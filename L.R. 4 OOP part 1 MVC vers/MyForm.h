#pragma once
#include "Container.h"
namespace LR4OOPpart1lastvers {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	static int fCtrl = 0;
	shapes circles;
	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			g = this->pBox->CreateGraphics();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pBox;
	protected:
	private: System::Windows::Forms::CheckBox^ cBoxCtrl;
	private: System::Windows::Forms::CheckBox^ cBoxMulty;
	private: Graphics^ g;
	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pBox = (gcnew System::Windows::Forms::PictureBox());
			this->cBoxCtrl = (gcnew System::Windows::Forms::CheckBox());
			this->cBoxMulty = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pBox))->BeginInit();
			this->SuspendLayout();
			// 
			// pBox
			// 
			this->pBox->Location = System::Drawing::Point(0, -2);
			this->pBox->Name = L"pBox";
			this->pBox->Size = System::Drawing::Size(717, 403);
			this->pBox->TabIndex = 0;
			this->pBox->TabStop = false;
			this->pBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pBox_Paint);
			this->pBox->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pBox_MouseClick);
			// 
			// cBoxCtrl
			// 
			this->cBoxCtrl->AutoSize = true;
			this->cBoxCtrl->Location = System::Drawing::Point(13, 12);
			this->cBoxCtrl->Name = L"cBoxCtrl";
			this->cBoxCtrl->Size = System::Drawing::Size(198, 20);
			this->cBoxCtrl->TabIndex = 1;
			this->cBoxCtrl->Text = L"¬ключить функционал ctrl";
			this->cBoxCtrl->UseVisualStyleBackColor = true;
			// 
			// cBoxMulty
			// 
			this->cBoxMulty->AutoSize = true;
			this->cBoxMulty->Location = System::Drawing::Point(12, 38);
			this->cBoxMulty->Name = L"cBoxMulty";
			this->cBoxMulty->Size = System::Drawing::Size(324, 20);
			this->cBoxMulty->TabIndex = 2;
			this->cBoxMulty->Text = L"¬ыделить несколько кругов по одному клику";
			this->cBoxMulty->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(715, 401);
			this->Controls->Add(this->cBoxMulty);
			this->Controls->Add(this->cBoxCtrl);
			this->Controls->Add(this->pBox);
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		void reDraw() {
			this->Refresh();
			this->Invalidate();
			circles.DrawAll(g);
		}
#pragma endregion
	private: System::Void pBox_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		circles.resetCurrent();
		int x = e->X;
		int y = e->Y;
		Shape* c;
		int counter = 0;
		for (int i = 0; i < circles.getSize(); i++) {
			c = circles.getCurrent();
			if (c->isPointInObj(x, y)) {
				counter++;
			}
			circles.next();
		}
		if (counter == 0) {
			circles.unslect();
			c = new CCircle(x, y, true);
			circles.push_back(c);
		}
		else {
			if (fCtrl == 0) circles.unclick();
			circles.resetCurrent();
			for (int i = 0; i < circles.getSize(); i++) {
				c = circles.getCurrent();
				if (c->isPointInObj(x, y) && !(c->getIsSlctd())) {
					c->setIsSlctd(true);
					c->setIsClckd(true);
					if (!(cBoxMulty->Checked)) break;
				}
				circles.next();
			}
		}
		reDraw();
	}

	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::ControlKey && cBoxCtrl->Checked) {
			fCtrl = 1;
		}
		else if (e->KeyCode == Keys::Delete) {
			circles.delSlctd();
			reDraw();
		}
	}
private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (e->KeyCode == Keys::ControlKey && cBoxCtrl->Checked) {
		fCtrl = 0;
	}
}
private: System::Void pBox_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	circles.DrawAll(g);
}
};
}
