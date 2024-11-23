#pragma once

namespace InventoryManagementBST {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class DetailsForm : public Form
    {
    //private:
    //    Action<int, String^, int>^ saveCallback; // Callback to save updated data
    //    Action<int>^ deleteCallback; // Callback to delete the item
    public:
        DetailsForm(int inventoryId, String^ description, int quantity)
        {
            InitializeComponent();

            // Set the fields with passed data
            this->inventoryIdTextBox->Text = inventoryId.ToString();
            this->descriptionTextBox->Text = description;
            this->quantityTextBox->Text = quantity.ToString();
        }

    private:
        Label^ inventoryIdLabel;
        Label^ descriptionLabel;
        Label^ quantityLabel;

        TextBox^ inventoryIdTextBox;
        TextBox^ descriptionTextBox;
        TextBox^ quantityTextBox;
        TextBox^ saveButton;

        Button^ deleteButton;

        void InitializeComponent()
        {
            this->inventoryIdLabel = gcnew Label();
            this->descriptionLabel = gcnew Label();
            this->quantityLabel = gcnew Label();

            this->inventoryIdTextBox = gcnew TextBox();
            this->descriptionTextBox = gcnew TextBox();
            this->quantityTextBox = gcnew TextBox();
            this->saveButton = gcnew TextBox();

            this->deleteButton = gcnew Button();

            // Labels
            this->inventoryIdLabel->Text = L"Inventory Id";
            this->inventoryIdLabel->Location = System::Drawing::Point(20, 20);
            this->descriptionLabel->Text = L"Description";
            this->descriptionLabel->Location = System::Drawing::Point(20, 70);
            this->quantityLabel->Text = L"Quantity";
            this->quantityLabel->Location = System::Drawing::Point(20, 120);

            // TextBoxes
            this->inventoryIdTextBox->Location = System::Drawing::Point(140, 20);
            this->inventoryIdTextBox->Size = System::Drawing::Size(200, 20);

            this->descriptionTextBox->Location = System::Drawing::Point(140, 70);
            this->descriptionTextBox->Size = System::Drawing::Size(200, 20);

            this->quantityTextBox->Location = System::Drawing::Point(140, 120);
            this->quantityTextBox->Size = System::Drawing::Size(200, 20);

            // Delete Button
            this->deleteButton->Text = L"Delete";
            this->deleteButton->Location = System::Drawing::Point(140, 170);
            this->deleteButton->Click += gcnew EventHandler(this, &DetailsForm::DeleteButton_Click);

            // Save Button
            this->saveButton->Text = L"Save";
            this->saveButton->Location = System::Drawing::Point(240, 170);
            this->saveButton->Click += gcnew EventHandler(this, &DetailsForm::SaveButton_Click);

            // Add controls to the form
            this->Controls->Add(this->inventoryIdLabel);
            this->Controls->Add(this->descriptionLabel);
            this->Controls->Add(this->quantityLabel);

            this->Controls->Add(this->inventoryIdTextBox);
            this->Controls->Add(this->descriptionTextBox);
            this->Controls->Add(this->quantityTextBox);

            this->Controls->Add(this->deleteButton);
            this->Controls->Add(this->saveButton);

            this->Text = L"Update Details";
            this->Size = System::Drawing::Size(400, 300);
        }

        void SaveButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            int inventoryId = Convert::ToInt32(this->inventoryIdTextBox->Text);
            String^ description = this->descriptionTextBox->Text;
            int quantity = Convert::ToInt32(this->quantityTextBox->Text);

            // Trigger the callback to update data
            //this->saveCallback(inventoryId, description, quantity);

            // Close the form after saving
            this->Close();
        }

        // Delete Button Click
        void DeleteButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            int inventoryId = Convert::ToInt32(this->inventoryIdTextBox->Text);

            // Trigger the callback to delete the item
            //this->deleteCallback(inventoryId);

            // Close the form after deletion
            this->Close();
        }
    };
}
