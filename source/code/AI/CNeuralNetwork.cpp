#include "CNeuralNetwork.h"
#include "CRandom.h"

#include <fstream>

CNeuralNetwork::CNeuralNetwork( std::vector<unsigned>& rTopology )
	: m_Topology( rTopology )
	, m_WeightMatrices()
	, m_BiasMatrices()
	, m_ValueMatrices()
	, m_HiddenActivation( RELU )
	, m_OutputActivation( SIGMOID )
{
	m_ValueMatrices.resize( m_Topology.size(), 0 );

	for( unsigned i = 0; i < m_Topology.size() - 1; i++ )
	{
		{	// Initalize random weights
			CMatrix WeightMatrix( m_Topology[i + 1], m_Topology[i] );
			for( float& rValue : WeightMatrix.GetValues() )
				rValue = Random( -1.f, 1.f ); // TODO: Maybe not hardcode random values

			m_WeightMatrices.push_back( std::move( WeightMatrix ) );
		}

		{	// Initalize random biases
			CMatrix BiasMatrix( m_Topology[i + 1], 1 );
			for( float& rValue : BiasMatrix.GetValues() )
				rValue = Random( -1.f, 1.f ); // TODO: Maybe not hardcode random values

			m_BiasMatrices.push_back( std::move( BiasMatrix ) );
		}
	}
}

bool CNeuralNetwork::Predict( const std::vector<float>& rInputs )
{
	if( rInputs.size() != m_Topology[0] )
		return false;

	// Create input matrix
	CMatrix InputMatrix( rInputs.size(), 1 );
	for( unsigned i = 0; i < rInputs.size(); i++ )
		InputMatrix[i] = rInputs[i];

	// Do feed forward calculations between layers
	for( unsigned i = 0; i < m_WeightMatrices.size(); i++ )
	{
		m_ValueMatrices[i] = InputMatrix;
		InputMatrix *= m_WeightMatrices[i];
		InputMatrix += m_BiasMatrices[i];

		if( i != m_WeightMatrices.size() - 1 )
		{
			for( float& rValue : InputMatrix.GetValues() )
				Activate( rValue, false );
		}
		else
		{
			for( float& rValue : InputMatrix.GetValues() )
				Activate( rValue, true );
		}
	}

	m_ValueMatrices[m_WeightMatrices.size()] = std::move( InputMatrix );
	return true;
}

bool CNeuralNetwork::SaveModel( const std::string FileName )
{
	std::ofstream File( "data/NNModels/" + FileName );
	if( !File.is_open() )
		return false;

	File << "Topology: ";
	for( unsigned& rValue : m_Topology )
		File << rValue << " ";

	File << "\nWeights:";
	for( CMatrix& rMatrix : m_WeightMatrices )
	{
		File << "\nMatrix: ";
		File << rMatrix.GetColumnSize() << " ";
		File << rMatrix.GetRowSize() << " ";

		for( float& rValue : rMatrix.GetValues() )
			File << rValue << " ";
	}

	File << "\nBiases:";
	for( CMatrix& rMatrix : m_BiasMatrices )
	{
		File << "\nMatrix: ";
		File << rMatrix.GetColumnSize() << " ";
		File << rMatrix.GetRowSize() << " ";

		for( float& rValue : rMatrix.GetValues() )
			File << rValue << " ";
	}

	File << "\nHiddenActivation: ";
	File << m_HiddenActivation << std::endl;

	File << "OutputActivation: ";
	File << m_OutputActivation << std::endl;

	File.close();
	return true;
}

bool CNeuralNetwork::LoadModel( const std::string FileName )
{
	std::ifstream File( "data/NNModels/" + FileName );
	if( !File.is_open() )
		return false;

	m_Topology.clear();
	m_WeightMatrices.clear();
	m_BiasMatrices.clear();
	m_ValueMatrices.clear();

	std::vector<CMatrix>* pMatrices = nullptr;
	std::string TextOnLine;
	while( std::getline( File, TextOnLine ) )
	{
		std::vector<std::string> Words( 1, "" );
		std::stringstream StringStream( TextOnLine );

		unsigned MatrixIndex = 0;
		while( StringStream >> Words.back() )
		{
			if( Words.front() == "Weights:" )
				pMatrices = &m_WeightMatrices;
			else if( Words.front() == "Biases:" )
				pMatrices = &m_BiasMatrices;
			else if( Words.front() == "Matrix:" )
			{
				if( Words.size() > 3 )
					pMatrices->back()[MatrixIndex++] = ( std::stof( Words.back() ) );
				else if( Words.size() > 2 )
					pMatrices->push_back( CMatrix( std::stoi( Words[1] ), std::stoi( Words[2] ) ) );
			}

			if( Words.size() > 1 )
			{
				if( Words.front() == "Topology:" )
					m_Topology.push_back( std::stoi( Words.back() ) );
				else if( Words.front() == "HiddenActivation:" )
					m_HiddenActivation = ( EActivation )std::stoi( Words.back() );
				else if( Words.front() == "OutputActivation:" )
					m_OutputActivation = ( EActivation )std::stoi( Words.back() );
			}

			Words.push_back( "" );
		}
	}

	m_ValueMatrices.resize( m_Topology.size() );
	return true;
}

void CNeuralNetwork::Activate( float& rValue, bool IsOutput )
{
	EActivation Activation = IsOutput ? m_OutputActivation : m_HiddenActivation;

	switch( Activation )
	{
		case CNeuralNetwork::SIGMOID:
		{
			Sigmoid( rValue );
			break;
		}
		case CNeuralNetwork::TANH:
		{
			Tanh( rValue );
			break;
		}
		case CNeuralNetwork::RELU:
		{
			ReLU( rValue );
			break;
		}
	}
}
