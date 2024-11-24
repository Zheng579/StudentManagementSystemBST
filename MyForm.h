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
            // Load data from Json;
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

        ref class BSTNode
        {
        public:
            InventoryItem^ Item;
            BSTNode^ Left;
            BSTNode^ Right;

            BSTNode(InventoryItem^ item)
            {
                Item = item;
                Left = nullptr;
                Right = nullptr;
            }
        };

        ref class InventoryBST
        {
        public:
            BSTNode^ Root;

            InventoryBST() { Root = nullptr; }

            void Insert(InventoryItem^ item)
            {
                Root = InsertIter(Root, item);
            }

            //insert new item //hit stack overflow issues when using 10000 record
            //BSTNode^ InsertRec(BSTNode^ root, InventoryItem^ item)
            //{
            //    //if no root
            //    if (root == nullptr)
            //        return gcnew BSTNode(item);

            //    //find the inserted invId
            //    if (item->InventoryId < root->Item->InventoryId)
            //        root->Left = InsertRec(root->Left, item);
            //    else if (item->InventoryId > root->Item->InventoryId)
            //        root->Right = InsertRec(root->Right, item);

            //    return root;
            //}

            //new insert to prevent iterative issue  avoids recursion and prevents stack overflow issues
            BSTNode^ InsertIter(BSTNode^ root, InventoryItem^ item)
            {
                // If the tree is empty, return a new node
                if (root == nullptr)
                    return gcnew BSTNode(item);

                BSTNode^ current = root;
                BSTNode^ parent = nullptr;

                // Traverse the tree iteratively
                while (current != nullptr)
                {
                    parent = current;

                    // If the item to insert has a smaller InventoryId, go to the left subtree
                    if (item->InventoryId < current->Item->InventoryId)
                        current = current->Left;
                    // If the item to insert has a larger InventoryId, go to the right subtree
                    else if (item->InventoryId > current->Item->InventoryId)
                        current = current->Right;
                    // If the item already exists, we do nothing (or could handle duplicates)
                    else
                        return root;
                }

                // Now we have found the appropriate position for insertion
                if (item->InventoryId < parent->Item->InventoryId)
                    parent->Left = gcnew BSTNode(item);
                else
                    parent->Right = gcnew BSTNode(item);

                return root;
            }

            InventoryItem^ Search(int id)
            {
                return SearchRec(Root, id);
            }

            //search BST with inventoryId
            InventoryItem^ SearchRec(BSTNode^ root, int id)
            {
                //if found item
                if (root == nullptr || root->Item->InventoryId == id)
                    return root != nullptr ? root->Item : nullptr;

                //if id < rootid, go to left and continue
                if (id < root->Item->InventoryId)
                    return SearchRec(root->Left, id);

                //if id > rootid, go to right and continue
                return SearchRec(root->Right, id);
            }

            void Delete(int id)
            {
                Root = DeleteRec(Root, id);
            }

            //delete from BST
            BSTNode^ DeleteRec(BSTNode^ root, int id)
            {
                if (root == nullptr) return root;

                //find the node
                if (id < root->Item->InventoryId)
                    root->Left = DeleteRec(root->Left, id);
                else if (id > root->Item->InventoryId)
                    root->Right = DeleteRec(root->Right, id);
                //node is found
                else
                {
                    //if only one child node is found
                    if (root->Left == nullptr)
                    {
                        BSTNode^ temp = root->Right;
                        delete root;
                        return temp;
                    }
                    else if (root->Right == nullptr)
                    {
                        BSTNode^ temp = root->Left;
                        delete root;
                        return temp;
                    }

                    //if 2 child node, take smallest value in right subtree
                    BSTNode^ temp = MinValueNode(root->Right);
                    root->Item = temp->Item;
                    root->Right = DeleteRec(root->Right, temp->Item->InventoryId);
                }
                return root;
            }

            //find the right subtree smallest node (in-order successor)
            BSTNode^ MinValueNode(BSTNode^ node)
            {
                BSTNode^ current = node;
                while (current && current->Left != nullptr)
                    current = current->Left;
                return current;
            }

            //Retrieve All the data (process left subtree then right subtree)
            void InOrderTraversal(BSTNode^ node, System::Collections::Generic::List<InventoryItem^>^% items)
            {
                if (node != nullptr)
                {
                    InOrderTraversal(node->Left, items);
                    items->Add(node->Item);
                    InOrderTraversal(node->Right, items);
                }
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

        // Local inventory data (BST)
        InventoryBST^ inventoryBST = gcnew InventoryBST();
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
        // Load data from JSON file into BST
        void LoadDataFromJson()
        {
            std::ifstream file("1000inventory.json");
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

                InventoryItem^ newItem = gcnew InventoryItem(id, description, quantity);
                inventoryBST->Insert(newItem);
                newItem = nullptr;
            }
            //PopulateGridView();
            file.close();
        }

        // Populate DataGridView by traversing BST in order
        void PopulateGridView()
        {
            System::Collections::Generic::List<InventoryItem^>^ items = gcnew System::Collections::Generic::List<InventoryItem^>();
            System::Diagnostics::Stopwatch^ stopwatch = System::Diagnostics::Stopwatch::StartNew();

            inventoryBST->InOrderTraversal(inventoryBST->Root, items);

            stopwatch->Stop();
            String^ elapsedTime = String::Format("Search All Operation completed in {0:F4} milliseconds.", (double)(stopwatch->ElapsedTicks/1000));

            this->inventoryGridView->Rows->Clear();
            for each (InventoryItem ^ item in items)
            {
                this->inventoryGridView->Rows->Add(item->InventoryId, item->Description, item->Quantity);
            }
            MessageBox::Show("Inventory retrieved all successfully!\n" + elapsedTime);
        }
#pragma endregion

#pragma region CRUD
        // Handle "Search All" button click
        void SearchAllButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ searchText = inputTextBox->Text->Trim();

            if (!String::IsNullOrEmpty(searchText))
            {
                int searchId;
                if (Int32::TryParse(searchText, searchId))
                {
                    System::Diagnostics::Stopwatch^ stopwatch = System::Diagnostics::Stopwatch::StartNew();
                    InventoryItem^ item = inventoryBST->Search(searchId);

                    stopwatch->Stop();
                    String^ elapsedTime = String::Format("Search Operation completed in {0:F4} milliseconds.", (stopwatch->ElapsedTicks/1000));

                    if (item != nullptr)
                    {
                        // Display search result in the DataGridView
                        inventoryGridView->Rows->Clear();
                        inventoryGridView->Rows->Add(item->InventoryId, item->Description, item->Quantity);
                        MessageBox::Show("Inventory retrieved successfully!\n" + elapsedTime);

                    }
                    else
                    {
                        stopwatch->Stop();
                        MessageBox::Show("Item not found.");
                    }
                }
                else
                {
                    MessageBox::Show("Please enter a valid Inventory Id.");
                }
            }
            else {
                PopulateGridView();
            }
        }

        // Handle update and delete actions
        void InventoryGridView_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0)
            {
                switch (e->ColumnIndex)
                {
                case 3: // Update button column
                {
                    int inventoryId = Convert::ToInt32(this->inventoryGridView->Rows[e->RowIndex]->Cells[0]->Value);
                    String^ description = this->inventoryGridView->Rows[e->RowIndex]->Cells[1]->Value->ToString();
                    int quantity = Convert::ToInt32(this->inventoryGridView->Rows[e->RowIndex]->Cells[2]->Value);

                    // Update the inventory
                    UpdateInventoryData(inventoryId, description, quantity);
                    break;
                }
                case 4: // Delete button column
                {
                    int inventoryId = Convert::ToInt32(this->inventoryGridView->Rows[e->RowIndex]->Cells[0]->Value);
                    DeleteInventoryData(inventoryId);
                    break;
                }
                }
            }
        }

        // Update inventory data in the BST
        void UpdateInventoryData(int inventoryId, String^ description, int quantity)
        {
            System::Diagnostics::Stopwatch^ stopwatch = System::Diagnostics::Stopwatch::StartNew();
            // Check if inventoryId is 0, in which case we perform an insert
            if (inventoryId == 0)
            {
                // Find the maximum inventoryId in the BST
                int maxInventoryId = FindMaxInventoryId(inventoryBST->Root);

                // Generate a new inventoryId as maxInventoryId + 1
                inventoryId = maxInventoryId + 1;

                // Create a new InventoryItem with the new inventoryId
                InventoryItem^ newItem = gcnew InventoryItem(inventoryId, description, quantity);

                // Insert the new item into the BST
                inventoryBST->Insert(newItem);

                stopwatch->Stop();
                String^ elapsedTime = String::Format("Insert Operation completed in {0:F4} milliseconds.", (stopwatch->ElapsedTicks/1000));

                MessageBox::Show("New inventory item inserted successfully!\n" + elapsedTime);
                PopulateGridView();
            }
            else {
                InventoryItem^ item = inventoryBST->Search(inventoryId);
                if (item != nullptr)
                {
                    item->Description = description;
                    item->Quantity = quantity;

                    stopwatch->Stop();
                    String^ elapsedTime = String::Format("Update Operation completed in {0:F4} milliseconds.", (stopwatch->ElapsedTicks/1000));

                    MessageBox::Show("Inventory updated successfully!\n" + elapsedTime);
                    PopulateGridView();
                }
                else
                {
                    stopwatch->Stop();
                    MessageBox::Show("Item not found for update.");
                }
            }
        }

        // Delete inventory data from the BST
        void DeleteInventoryData(int inventoryId)
        {
            inventoryBST->Delete(inventoryId);
            PopulateGridView();
            MessageBox::Show("Inventory deleted successfully!");
        }
#pragma endregion

#pragma region Helper
        // Helper function to find the maximum inventoryId in the BST
        int FindMaxInventoryId(BSTNode^ node)
        {
            // Traverse to the rightmost node to find the maximum inventoryId
            if (node == nullptr)
            {
                return 0;  // Return 0 if the tree is empty
            }
            while (node->Right != nullptr)
            {
                node = node->Right;
            }
            return node->Item->InventoryId;  // Return the inventoryId of the rightmost node
        }
#pragma endregion
    };
}
