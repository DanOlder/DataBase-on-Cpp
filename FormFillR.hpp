#pragma once

namespace DataBaseonC {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FormFill
	/// </summary>
	public ref class FormFillR : public System::Windows::Forms::Form
	{
	public:
		FormFillR(RecordLabel_strc* dataTemp)
		{
			data = dataTemp;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FormFillR()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ button1;
	protected:

	private:
		RecordLabel_strc* data;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(284, 133);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(232, 29);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &FormFillR::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(51, 133);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(184, 24);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Record Label Name:";
			this->label1->Click += gcnew System::EventHandler(this, &FormFillR::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(51, 199);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(135, 24);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Year of Found:";
			this->label2->Click += gcnew System::EventHandler(this, &FormFillR::label2_Click);
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(284, 199);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(232, 29);
			this->textBox2->TabIndex = 2;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(198, 310);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(166, 62);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Enter";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &FormFillR::button1_Click);
			// 
			// FormFill
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(568, 435);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"FormFill";
			this->Text = L"FormFill";
			this->Load += gcnew System::EventHandler(this, &FormFillR::FormFill_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void FormFill_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

	msclr::interop::marshal_context context;
	data->label_name = context.marshal_as<std::string>(textBox1->Text);
	data->year_of_found = Convert::ToInt32(textBox2->Text);
	
	MessageBox::Show("Data's been sucsessfully recorded", "Done");
	this->Close();
}
};
}
