#pragma once
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

namespace InventoryManagementBST {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            //load data from Json;
            LoadDataFromJson();
        }
#pragma region InventoryItem Class
        ref class InventoryItem
        {
        public:
            int InventoryId;
            String^ Description;
            int Quantity;

            InventoryItem(int id, String^ desc, int qty)
            {
                InventoryId = id;
                Description = desc;
                Quantity = qty;
            }
        };
#pragma endregion

#pragma region End Initialized UI
    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Button^ searchAllButton;
        System::Windows::Forms::TextBox^ inputTextBox;
        System::Windows::Forms::DataGridView^ inventoryGridView;

        System::ComponentModel::Container^ components;
        System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn1;
        System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn2;
        System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn3;
        System::Windows::Forms::DataGridViewButtonColumn^ Action;
        System::Windows::Forms::DataGridViewButtonColumn^ Delete;

        // Local inventory data
        System::Collections::Generic::List<InventoryItem^>^ inventoryList = gcnew System::Collections::Generic::List<InventoryItem^>();
#pragma endregion

#pragma region Windows Form Designer generated code
    public:
        void InitializeComponent(void)
        {
            this->searchAllButton = (gcnew System::Windows::Forms::Button());
            this->inputTextBox = (gcnew System::Windows::Forms::TextBox());
            this->inventoryGridView = (gcnew System::Windows::Forms::DataGridView());
            this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->Action = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
            this->Delete = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inventoryGridView))->BeginInit();
            this->SuspendLayout();
            // 
            // searchAllButton
            // 
            this->searchAllButton->Location = System::Drawing::Point(20, 20);
            this->searchAllButton->Name = L"searchAllButton";
            this->searchAllButton->Size = System::Drawing::Size(100, 30);
            this->searchAllButton->TabIndex = 0;
            this->searchAllButton->Text = L"Search All";
            this->searchAllButton->UseVisualStyleBackColor = true;
            this->searchAllButton->Click += gcnew System::EventHandler(this, &MyForm::SearchAllButton_Click);
            // 
            // inputTextBox
            // 
            this->inputTextBox->Location = System::Drawing::Point(140, 25);
            this->inputTextBox->Name = L"inputTextBox";
            this->inputTextBox->Size = System::Drawing::Size(300, 20);
            this->inputTextBox->TabIndex = 1;
            // 
            // inventoryGridView
            // 
            this->inventoryGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->inventoryGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
                this->dataGridViewTextBoxColumn1,
                    this->dataGridViewTextBoxColumn2, this->dataGridViewTextBoxColumn3, this->Action, this->Delete
            });
            this->inventoryGridView->Location = System::Drawing::Point(20, 70);
            this->inventoryGridView->Name = L"inventoryGridView";
            this->inventoryGridView->Size = System::Drawing::Size(800, 500);
            this->inventoryGridView->TabIndex = 2;
            this->inventoryGridView->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::InventoryGridView_CellContentClick);
            // 
            // dataGridViewTextBoxColumn1
            // 
            this->dataGridViewTextBoxColumn1->HeaderText = L"Inventory Id";
            this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
            this->dataGridViewTextBoxColumn1->ReadOnly = true;
            // 
            // dataGridViewTextBoxColumn2
            // 
            this->dataGridViewTextBoxColumn2->HeaderText = L"Inventory Description";
            this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
            // 
            // dataGridViewTextBoxColumn3
            // 
            this->dataGridViewTextBoxColumn3->HeaderText = L"Quantity";
            this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
            // 
            // Action
            // 
            this->Action->HeaderText = L"Update";
            this->Action->Name = L"Action";
            this->Action->Text = L"Update";
            // 
            // Delete
            // 
            this->Delete->HeaderText = L"Delete";
            this->Delete->Name = L"Delete";
            this->Delete->Text = L"Delete";
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(857, 628);
            this->Controls->Add(this->searchAllButton);
            this->Controls->Add(this->inputTextBox);
            this->Controls->Add(this->inventoryGridView);
            this->Name = L"MyForm";
            this->Text = L"Inventory Management";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inventoryGridView))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
#pragma region Load From Json
        //Initialized data: Load data from JSON
        void LoadDataFromJson()
        {
            std::ifstream file("inventory.json");
            if (!file.is_open())
            {
                MessageBox::Show("Unable to open JSON file.");
                return;
            }

            nlohmann::json jsonData;
            file >> jsonData;

            for (const auto& item : jsonData)
            {
                int id = item["InventoryId"];
                String^ description = gcnew String(item["Description"].get<std::string>().c_str());
                int quantity = item["Quantity"];

                inventoryList->Add(gcnew InventoryItem(id, description, quantity));
            }
            PopulateGridView();
            file.close();
        }


        // Populate DataGridView
        void PopulateGridView()
        {
            this->inventoryGridView->Rows->Clear();
            for each (InventoryItem ^ item in inventoryList)
            {
                this->inventoryGridView->Rows->Add(item->InventoryId, item->Description, item->Quantity);
            }
        }
#pragma endregion

#pragma region CRUD
        // Handle "Search All" button click
        void SearchAllButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ searchText = inputTextBox->Text->Trim(); // Get the input text and remove any leading/trailing whitespace

            if (!String::IsNullOrEmpty(searchText))
            {
                // Filter the inventory list based on the input value (InventoryId)
                int searchId;
                if (Int32::TryParse(searchText, searchId)) // Try to parse the input as an integer
                {
                    System::Collections::Generic::List<InventoryItem^>^ filteredList = gcnew System::Collections::Generic::List<InventoryItem^>();
                    for each (InventoryItem ^ item in inventoryList)
                    {
                        if (item->InventoryId == searchId) // Match InventoryId
                        {
                            filteredList->Add(item);
                        }
                    }
                    inventoryList = filteredList; // Update the list with the filtered results
                }
                else
                {
                    MessageBox::Show("Please enter a valid Inventory Id.");
                    return; // Return if input is not a valid number
                }
            }
        }

        // Handle update and delete actions
        void InventoryGridView_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0) // Ensure valid row index
            {
                switch (e->ColumnIndex)
                {
                    case 3: // Update button column
                    {
                        int inventoryId = Convert::ToInt32(this->inventoryGridView->Rows[e->RowIndex]->Cells[0]->Value);
                        String^ description = this->inventoryGridView->Rows[e->RowIndex]->Cells[1]->Value->ToString();
                        int quantity = Convert::ToInt32(this->inventoryGridView->Rows[e->RowIndex]->Cells[2]->Value);

                        // Update the inventory directly within the list
                        UpdateInventoryData(inventoryId, description, quantity);
                        break;
                    }
                    case 4: // Delete button column
                    {
                        int inventoryId = Convert::ToInt32(this->inventoryGridView->Rows[e->RowIndex]->Cells[0]->Value);
                        DeleteInventoryData(inventoryId);
                        break;
                    }
                    default:
                        // Optional: Handle other cases or do nothing
                        break;
                }
            }
        }

        // Update inventory data directly in the list
        void UpdateInventoryData(int inventoryId, String^ description, int quantity)
        {
            //add new record if no inventoryId
            if (inventoryId == 0) {
                InventoryItem^ lastItem = inventoryList[inventoryList->Count - 1];
                int newId = lastItem->InventoryId + 1;  // Assuming 'ID' is a public property of 'item'

                inventoryList->Add(gcnew InventoryItem(newId, description, quantity));
            }
            //update record if inventoryId exists
            else {
                for each (InventoryItem ^ item in inventoryList)
                {
                    if (item->InventoryId == inventoryId)
                    {
                        item->Description = description;
                        item->Quantity = quantity;
                        break;
                    }
                }
            }

            PopulateGridView(); // Refresh the grid view with updated data
            MessageBox::Show("Inventory updated successfully!"); // Show success message
        }

        // Delete inventory data
        void DeleteInventoryData(int inventoryId)
        {
            for (int i = 0; i < inventoryList->Count; i++)
            {
                if (inventoryList[i]->InventoryId == inventoryId)
                {
                    inventoryList->RemoveAt(i);
                    break;
                }
            }

            PopulateGridView();
            MessageBox::Show("Inventory deleted successfully!");
        }
#pragma endregion
    };
}
