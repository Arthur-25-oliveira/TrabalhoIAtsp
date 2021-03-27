#pragma once

#include <time.h>
#include "Populacao.hpp"
#include <stdlib.h>
#include <sstream>
#include <random>
#include <cmath>

#include "TSPGraph.hpp"

namespace GeneticAlgorithm {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  generatePahtButton;
	protected:

	private: System::Windows::Forms::RichTextBox^  richTextBoxOutput;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::NumericUpDown^  verticesUpDown;
	private: System::Windows::Forms::Label^  label1;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		void Selecao(Populacao &p, Individuo &primeiro, Individuo &segundo)
		{
			//Seleciona o individuo mais fit
			primeiro = p.GetFittest();

			//Seleciona o segundo mais fit
			segundo = p.GetSegundoFittest();
		}

		void Crossover(Individuo &primeiro, Individuo &segundo)
		{
			//Sorteia o ponto de crossover
			int crossOverPoint = rand() % primeiro.GetQtdGenes();

			//Troca os valores dos genes
			for (int i = 0; i < crossOverPoint; i++)
			{
				int temp = primeiro.genes[i];
				primeiro.genes[i] = segundo.genes[i];
				segundo.genes[i] = temp;
			}
		}

		void Mutacao(Individuo &primeiro, Individuo &segundo)
		{

			//Sorteia um ponto de mtacao
			int mutationPoint = rand() % primeiro.GetQtdGenes();

			//Inverte o valor naquele ponto
			if (primeiro.genes[mutationPoint] == 0) {
				primeiro.genes[mutationPoint] = 1;
			}
			else {
				primeiro.genes[mutationPoint] = 0;
			}

			mutationPoint = rand() % primeiro.GetQtdGenes();

			if (segundo.genes[mutationPoint] == 0) {
				segundo.genes[mutationPoint] = 1;
			}
			else {
				segundo.genes[mutationPoint] = 0;
			}
		}

	private: void GenerateGenetic()
	{
		srand(time(0));


		Individuo primeiroFit;
		Individuo segundoFit;
		const int maxIterationsAllowed = 100;

		//Gerar Populacao Inicial
		int numGenes = 5;
		Populacao populacao(10, numGenes); // 10 individuos, com 5 genes cada
		int contGeracao = 0;

		// Calcular Fitness
		populacao.CalcularFitnessIndividuos();
		//std::cout << "Geração " << contGeracao << " - Maior Fit: " << populacao.GetFittestValue() << std::endl;

		std::stringstream output;
		output << "Geração " << contGeracao << " - Maior Fit: " << populacao.GetFittestValue() << std::endl;
		richTextBoxOutput->AppendText(gcnew String(output.str().c_str()));

		//Enquanto nao convergir
		while (populacao.GetFittestValue() < numGenes && maxIterationsAllowed > contGeracao)
		{
			contGeracao++;

			//Seleção
			Selecao(populacao, primeiroFit, segundoFit);

			//Crossover
			Crossover(primeiroFit, segundoFit);

			//Aplica Mutação considerando percentual
			if (rand() % 7 < 5)
				Mutacao(primeiroFit, segundoFit);

			//Adiciona o mais saudavel na populacao, no lugar do menos fit
			primeiroFit.CalcularFitness();
			segundoFit.CalcularFitness();

			//Verifica o mais fit da nova geracao e insere na populacao
			if (primeiroFit.GetFitness() > segundoFit.GetFitness())
				populacao.individuos[populacao.GetPosMenosFittest()] = primeiroFit;
			else
				populacao.individuos[populacao.GetPosMenosFittest()] = segundoFit;


			//Calcular fitness
			populacao.CalcularFitnessIndividuos();
			//std::cout << "Geração " << contGeracao << " - Maior Fit: " << populacao.GetFittestValue() << std::endl;
			output << "Geração " << contGeracao << " - Maior Fit: " << populacao.GetFittestValue() << std::endl;
			richTextBoxOutput->AppendText(gcnew String(output.str().c_str()));
		}

		//std::cout << "Solucionado na geracao " << contGeracao << ", com fitness: " << populacao.GetFittestValue() << std::endl;
		output << "Solucionado na geracao " << contGeracao << ", com fitness: " << populacao.GetFittestValue() << std::endl;
		richTextBoxOutput->AppendText(gcnew String(output.str().c_str()));

		Individuo finalIndiv = populacao.GetFittest();
		DrawLines(finalIndiv);
	}

	private: void DrawLines(const Individuo& bestIndividuo)
	{
		Drawing::Pen blackPen(Drawing::Color::Black, 3);
		//int x1 = checkBoxPassoFundo->Left;
		//int y1 = checkBoxPassoFundo->Top;
		//int x2 = checkBoxPortoAlegre->Left;
		//int y2 = checkBoxPortoAlegre->Top;

		//std::stringstream output;
		//output << "X1 " << x1 << " y1 " << y1 << " x2 " << x2 << " y2 " << y2 << std::endl;

		//richTextBoxOutput->AppendText(gcnew String(output.str().c_str()));

		//Drawing::Point p1(x1, y1);
		//Drawing::Point p2(x2, y2);

	}

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->generatePahtButton = (gcnew System::Windows::Forms::Button());
				 this->richTextBoxOutput = (gcnew System::Windows::Forms::RichTextBox());
				 this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
				 this->verticesUpDown = (gcnew System::Windows::Forms::NumericUpDown());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->verticesUpDown))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // generatePahtButton
				 // 
				 this->generatePahtButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->generatePahtButton->ForeColor = System::Drawing::SystemColors::ControlText;
				 this->generatePahtButton->Location = System::Drawing::Point(12, 12);
				 this->generatePahtButton->Name = L"generatePahtButton";
				 this->generatePahtButton->Size = System::Drawing::Size(302, 36);
				 this->generatePahtButton->TabIndex = 0;
				 this->generatePahtButton->Text = L"Gera caminho";
				 this->generatePahtButton->UseVisualStyleBackColor = true;
				 this->generatePahtButton->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
				 // 
				 // richTextBoxOutput
				 // 
				 this->richTextBoxOutput->Location = System::Drawing::Point(12, 311);
				 this->richTextBoxOutput->Name = L"richTextBoxOutput";
				 this->richTextBoxOutput->ReadOnly = true;
				 this->richTextBoxOutput->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
				 this->richTextBoxOutput->Size = System::Drawing::Size(731, 89);
				 this->richTextBoxOutput->TabIndex = 2;
				 this->richTextBoxOutput->Text = L"";
				 // 
				 // pictureBox1
				 // 
				 this->pictureBox1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
				 this->pictureBox1->Location = System::Drawing::Point(12, 65);
				 this->pictureBox1->Name = L"pictureBox1";
				 this->pictureBox1->Size = System::Drawing::Size(730, 240);
				 this->pictureBox1->TabIndex = 3;
				 this->pictureBox1->TabStop = false;
				 // 
				 // verticesUpDown
				 // 
				 this->verticesUpDown->Location = System::Drawing::Point(481, 15);
				 this->verticesUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
				 this->verticesUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 this->verticesUpDown->Name = L"verticesUpDown";
				 this->verticesUpDown->Size = System::Drawing::Size(123, 20);
				 this->verticesUpDown->TabIndex = 4;
				 this->verticesUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(355, 17);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(120, 13);
				 this->label1->TabIndex = 5;
				 this->label1->Text = L"Quantidade de cidades:";
				 // 
				 // MyForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(755, 408);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->verticesUpDown);
				 this->Controls->Add(this->pictureBox1);
				 this->Controls->Add(this->richTextBoxOutput);
				 this->Controls->Add(this->generatePahtButton);
				 this->Name = L"MyForm";
				 this->Text = L"MyForm";
				 this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->verticesUpDown))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}

	private: float distance(int x1, int y1, int x2, int y2) {
		return sqrt(pow(x2 - x1, 2.0f) + pow(y2 - y1, 2.0f));
	}


	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		constexpr int dotSize = 15;
		//int verticesNum = verticesUpDown->Value.ToInt32(verticesUpDown->Value);
		//std::string val = std::to_string(verticesNum) + "\n";

		//richTextBoxOutput->AppendText(gcnew System::String(val.c_str()));
		/*
		--------------------------------------------------------------
		Desenha os pontos na tela
		--------------------------------------------------------------
		*/

		
		int w = pictureBox1->Width;
		int h = pictureBox1->Height;
		pictureBox1->Image = gcnew Bitmap(w, h);
		Graphics^ g = Graphics::FromImage(pictureBox1->Image);
		Brush^ bsh = gcnew SolidBrush(Color::White);
		g->FillRectangle(bsh, 0, 0, w, h);

		Brush^ bshGreen = gcnew SolidBrush(Color::Green);

		//Gera pontos baseado no verticesUpDown
		int verticesNum = verticesUpDown->Value.ToInt32(verticesUpDown->Value);
		VerticePoints initialPoints;

		//Pontos randomicos
		std::default_random_engine generator;
		std::uniform_int_distribution<int> widthRandon(0, w - int(0.05 * w));
		std::uniform_int_distribution<int> heightRandom(0, h - int(0.05 * h));
		

		for (int i = 0; i < verticesNum; i++) {
			auto wR = widthRandon(generator);
			auto hR = heightRandom(generator);
			g->FillEllipse(bshGreen, wR, hR, dotSize, dotSize);

			//Salva na lista
			initialPoints.push_back({ wR, hR });
		}

		/*
		--------------------------------------------------------------
		Faz o processamento dos pontos criados
		--------------------------------------------------------------
		*/
		
		//Gera o grafo
		ListOfCities edgeInitialList;
		int from = 0, to;

		for (auto p1 : initialPoints) {
			auto x1 = p1.first;
			auto y1 = p1.second;
			to = 0;
			for (auto p2 : initialPoints) {
				auto x2 = p2.first;
				auto y2 = p2.second;
				auto dist = distance(x1, y1, x2, y2);
				if (p1 != p2) {
					edgeInitialList.push_back({ std::to_string(from), std::to_string(to), dist});
				}
				to++;
			}
			from++;
		}

		//Roda o algoritmo genetico em approach parecido com o da aula		
		runGenetic(edgeInitialList, richTextBoxOutput, initialPoints.size());
		
		//pega o resultado
		auto resultPath = decodingIntVector();

		Pen^  blackPen = gcnew Pen(Color::Black, 3);
		//desenha o caminho
		for (int i = 0; i < resultPath.size() - 1; i++){
			auto it = resultPath[i];
			auto itNext = resultPath[i + 1];
			const auto& p1 = initialPoints[it];
			const auto& p2 = initialPoints[itNext];

			Point p1Obj = Point(p1.first + dotSize / 2, p1.second + dotSize / 2);
			Point p2Obj = Point(p2.first + dotSize / 2, p2.second + dotSize / 2);

			g->DrawLine(blackPen, p1Obj, p2Obj);
		}
	}

	};
}
