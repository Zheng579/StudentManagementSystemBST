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

        // Local inventory data
        System::Collections::Generic::List<InventoryItem^>^ inventoryList = gcnew System::Collections::Generic::List<InventoryItem^>();

#pragma region Windows Form Designer generated code
    public:
        void InitializeComponent(void)
        {
            this->searchAllButton = (gcnew System::Windows::Forms::Button());
            this->inputTextBox = (gcnew System::Windows::Forms::TextBox());
            this->inventoryGridView = (gcnew System::Windows::Forms::DataGridView());
            this->SuspendLayout();

            // 
            // searchAllButton
            // 
            this->searchAllButton->Location = System::Drawing::Point(20, 20);
            this->searchAllButton->Name = L"searchAllButton";
            this->searchAllButton->Size = System::Drawing::Size(100, 30);
            this->searchAllButton->Text = L"Search All";
            this->searchAllButton->UseVisualStyleBackColor = true;
            this->searchAllButton->Click += gcnew System::EventHandler(this, &MyForm::SearchAllButton_Click);

            // 
            // inputTextBox
            // 
            this->inputTextBox->Location = System::Drawing::Point(140, 25);
            this->inputTextBox->Name = L"inputTextBox";
            this->inputTextBox->Size = System::Drawing::Size(300, 20);

            // 
            // inventoryGridView
            // 
            this->inventoryGridView->Location = System::Drawing::Point(20, 70);
            this->inventoryGridView->Name = L"inventoryGridView";
            this->inventoryGridView->Size = System::Drawing::Size(800, 500);
            this->inventoryGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;

            // Adding columns
            this->inventoryGridView->Columns->Add("InventoryId", "Inventory Id");
            this->inventoryGridView->Columns->Add("InventoryDescription", "Inventory Description");
            this->inventoryGridView->Columns->Add("Quantity", "Quantity");

            // Add Delete and Update button columns
            DataGridViewButtonColumn^ deleteButton = gcnew DataGridViewButtonColumn();
            deleteButton->HeaderText = "Action";
            deleteButton->Text = "Delete";
            deleteButton->UseColumnTextForButtonValue = true;
            this->inventoryGridView->Columns->Add(deleteButton);

            DataGridViewButtonColumn^ updateButton = gcnew DataGridViewButtonColumn();
            updateButton->HeaderText = "";
            updateButton->Text = "Update";
            updateButton->UseColumnTextForButtonValue = true;
            this->inventoryGridView->Columns->Add(updateButton);

            // Add event handler for button clicks
            this->inventoryGridView->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::InventoryGridView_CellContentClick);

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
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private:
        // Load data from JSON
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
            else
            {
                // If input is empty, show all items
                LoadDataFromJson(); // Re-load the data from the JSON file
            }

            PopulateGridView(); // Populate the grid with the filtered or full list
        }

        // Handle update and delete actions
        void InventoryGridView_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0)
            {
                if (e->ColumnIndex == 3) // Delete button
                {
                    int inventoryId = Convert::ToInt32(this->inventoryGridView->Rows[e->RowIndex]->Cells[0]->Value);
                    DeleteInventoryData(inventoryId);
                }
                else if (e->ColumnIndex == 4) // Update button
                {
                    int inventoryId = Convert::ToInt32(this->inventoryGridView->Rows[e->RowIndex]->Cells[0]->Value);
                    String^ description = this->inventoryGridView->Rows[e->RowIndex]->Cells[1]->Value->ToString();
                    int quantity = Convert::ToInt32(this->inventoryGridView->Rows[e->RowIndex]->Cells[2]->Value);

                    // Update the inventory directly within the list
                    UpdateInventoryData(inventoryId, description, quantity);
                }
            }
        }

        // Update inventory data directly in the list
        void UpdateInventoryData(int inventoryId, String^ description, int quantity)
        {
            for each (InventoryItem ^ item in inventoryList)
            {
                if (item->InventoryId == inventoryId)
                {
                    item->Description = description;
                    item->Quantity = quantity;
                    break;
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
    };
}
