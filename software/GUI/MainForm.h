#pragma once

#include "LEDMatrixGUI.h"
#include "WebserverGUI.h"
#include <LedPanel.h>
#include <PixelImgType.h>
#include <app/tetris/TetrisApp.h>
#include <app/default/DefaultApp.h>
#include <app/settings/SettingsApp.h>
#include <app/pixelIt/PixelItApp.h>
#include <app/clock/ClockApp.h>
#include <app/spaceInvaders/SpaceInvadersApp.h>
#include <app/images/ImagesApp.h>
#include <app/snake/SnakeApp.h>

namespace PixelWallGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;

	LedPanel panel;
	
	/// <summary>
	/// Zusammenfassung für MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{

	public: System::Windows::Forms::VScrollBar^  vScrollBar1;


			 int OFF_X = 20;
			 int OFF_Y = 50;
			 int SPACE = 21;
			 int SIZE = 20;
			 int COLS = 12;
			 int ROWS = 18;
			 array<System::Windows::Forms::Label^, 1>^ labels = gcnew array<System::Windows::Forms::Label^, 1>(216);

			 delegate void ManagedSummer(uint8_t* payload, uint8_t len);
			 ManagedSummer^ managed = gcnew ManagedSummer(this, &MainForm::sendWebsocketData);
			 IntPtr stubPointer = Marshal::GetFunctionPointerForDelegate(managed);

	private: System::Windows::Forms::Timer^  timer1;

	private:
		static const int NUM_OF_APPS = 8;
		DefaultApp* defaultApp = new DefaultApp(&panel);
		SettingsApp* settingsApp = new SettingsApp(&panel);
		TetrisApp* tetrisApp = new TetrisApp(&panel, static_cast<void(*)(char*, uint8_t)>(stubPointer.ToPointer()));
		PixelItApp* pixelItApp = new PixelItApp(&panel, static_cast<void(*)(char*, uint8_t)>(stubPointer.ToPointer()));
		ClockApp* clockApp = new ClockApp(&panel);
		SpaceInvadersApp* spaceInvadersApp = new SpaceInvadersApp(&panel, static_cast<void(*)(char*, uint8_t)>(stubPointer.ToPointer()));
		ImagesApp* imagesApp = new ImagesApp(&panel);
		SnakeApp* snakeApp = new SnakeApp(&panel, static_cast<void(*)(char*, uint8_t)>(stubPointer.ToPointer()));

		IPixelApp* currApp = defaultApp;

		array<IPixelApp*> ^intArr;

		array<IPixelApp*, 1>^ allApps = gcnew array<IPixelApp*, 1>(NUM_OF_APPS);

	public:
		Thread ^ timerThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::timerInterrupt));
	private: System::Windows::Forms::Label^  label1;
	public:

	public:

		WebserverGUI webserver;

		void sendWebsocketData(uint8_t* payload, uint8_t len)
		{
			webserver.sendData(payload, len);
		}

		WebsiteResponse_t webServerRequest(String request, String parameter)
		{
			for (unsigned int i = 0; i < NUM_OF_APPS; i++)
			{
				if (allApps[i]->getName() == request)
				{
					if (currApp != allApps[i])
					{
						currApp->end();
						currApp = allApps[i];
						currApp->start();
					}
					return currApp->getWebsiteResponse(parameter);
				}
			}

			

			return WebSites::errorPage404;
		}

		void webSocketEvent(uint8_t* payload, uint8_t length)
		{
			currApp->newWebsocketData(payload, length);
		}


	public:
		MainForm(void):
			webserver(gcnew WebserverGUI::ResponseCallback(this, &MainForm::webServerRequest), gcnew WebserverGUI::WebsocketDataCallback(this, &MainForm::webSocketEvent))
		{

			InitializeComponent();

			allApps[0] = defaultApp;
			allApps[1] = settingsApp;
			allApps[2] = tetrisApp;
			allApps[3] = pixelItApp;
			allApps[4] = clockApp;
			allApps[5] = spaceInvadersApp;
			allApps[6] = imagesApp;
			allApps[7] = snakeApp;

			for (int y = 0; y < 18; y++)
			{
				for (int x = 0; x < 12; x++)
				{
					int index = y * 12 + x;

					labels[index] = (gcnew System::Windows::Forms::Label());

					labels[index]->Left = OFF_X + x * SPACE;
					labels[index]->Top = OFF_Y + y * SPACE;
					labels[index]->Parent = this;
					labels[index]->Width = SIZE;
					labels[index]->Height = SIZE;
					labels[index]->BackColor = System::Drawing::Color::Black;
					labels[index]->Visible = true;
					Controls->Add(labels[index]);
				}
			}

			panel.ledMatrix.setLabel(labels);

			this->ResumeLayout(false);
			this->PerformLayout();

			timerThread->Start();

			webserver.Run();

			this->Visible = false;

			currApp->start();
		}

		void timerInterrupt()
		{
			while (1)
			{
				currApp->timerTick();
				Thread::Sleep(10);
			}
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^  components;
	protected:

	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->vScrollBar1 = (gcnew System::Windows::Forms::VScrollBar());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// vScrollBar1
			// 
			this->vScrollBar1->Location = System::Drawing::Point(312, 54);
			this->vScrollBar1->Name = L"vScrollBar1";
			this->vScrollBar1->Size = System::Drawing::Size(20, 193);
			this->vScrollBar1->TabIndex = 1;
			this->vScrollBar1->Value = 100;
			this->vScrollBar1->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MainForm::vScrollBar1_Scroll);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(76, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"localhost:8080";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(336, 468);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->vScrollBar1);
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"Pixel Wall Simulator";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void vScrollBar1_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
		panel.ledMatrix.brightness = vScrollBar1->Value;
		panel.ledMatrix.show();
	}
private: System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	timerThread->Abort();
}
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	currApp->loop();
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {

}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {

}
};
}
