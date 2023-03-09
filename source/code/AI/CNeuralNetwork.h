#pragma once

#include "CMatrix.h"

#include <vector>
#include <string>

class CNeuralNetwork
{
public:
	enum EActivation
	{
		SIGMOID,
		TANH,
		RELU,
	};

	CNeuralNetwork( const std::string FileName ) { LoadModel( FileName ); }
	CNeuralNetwork( std::vector<unsigned>& rTopology );

	bool Predict( std::vector<float>& rInputs );
	float GetPrediction( unsigned OutputIndex ) { return m_ValueMatrices.back().GetValues()[OutputIndex]; }
	const std::vector<float>& GetAllPredictions( void ) { return m_ValueMatrices.back().GetValues(); }

	void SetHiddenActivation( EActivation Activation ) { m_HiddenActivation = Activation; }
	void SetOutputActivation( EActivation Activation ) { m_OutputActivation = Activation; }

	void SaveModel( const std::string FileName = "NeuralNetwork.txt" );
	bool LoadModel( const std::string FileName = "NeuralNetwork.txt" );

private:
	void Activate( float& rValue, bool IsOutput = false );
	void Sigmoid( float& rValue ) { rValue = 1 / ( 1 + exp( -rValue ) ); }
	void Tanh( float& rValue ) { rValue = ( exp( rValue ) - exp( -rValue ) ) / ( exp( rValue ) + exp( -rValue ) ); }
	void ReLU( float& rValue ) { rValue = std::max( 0.f, rValue ); }

	std::vector<unsigned> m_Topology;
	std::vector<CMatrix> m_WeightMatrices;
	std::vector<CMatrix> m_BiasMatrices;
	std::vector<CMatrix> m_ValueMatrices;

	EActivation m_HiddenActivation;
	EActivation m_OutputActivation;
};