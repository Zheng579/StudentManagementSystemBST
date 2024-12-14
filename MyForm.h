#pragma once
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <random>
#include <msclr/marshal_cppstd.h> 
#include <iostream>

namespace StudentManagementSystemBST {
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
        String^ fileName = "student_data10.json";
#pragma region InventoryItem Class
        ref class StudentInfo
        {
        public:
            int StudentId;
            String^ Name;
            String^ Course;
            int Year;

            StudentInfo(int id, String^ name, String^ course, int year)
            {
                StudentId = id;
                Name = name;
                Course = course;
                Year = year;
            }
        };

        ref class BSTNode
        {
        public:
            StudentInfo^ Item;
            BSTNode^ Left;
            BSTNode^ Right;

            BSTNode(StudentInfo^ item)
            {
                Item = item;
                Left = nullptr;
                Right = nullptr;
            }
        };

        ref class StudentBST
        {
        public:
            BSTNode^ Root;

            StudentBST() { Root = nullptr; }

            void Insert(StudentInfo^ item)
            {
                Root = InsertRec(Root, item);
            }

            //insert new item
            BSTNode^ InsertRec(BSTNode^ root, StudentInfo^ item)
            {
                //if no root
                if (root == nullptr)
                    return gcnew BSTNode(item);

                //find the inserted invId
                if (item->StudentId < root->Item->StudentId)
                    root->Left = InsertRec(root->Left, item);
                else if (item->StudentId > root->Item->StudentId)
                    root->Right = InsertRec(root->Right, item);

                return root;
            }

            StudentInfo^ Search(int id)
            {
                return SearchRec(Root, id);
            }

            //search BST with inventoryId
            StudentInfo^ SearchRec(BSTNode^ root, int id)
            {
                //if found item
                if (root == nullptr || root->Item->StudentId == id)
                    return root != nullptr ? root->Item : nullptr;

                //if id < rootid, go to left and continue
                if (id < root->Item->StudentId)
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
                if (id < root->Item->StudentId)
                    root->Left = DeleteRec(root->Left, id);
                else if (id > root->Item->StudentId)
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
                    root->Right = DeleteRec(root->Right, temp->Item->StudentId);
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

            //retrieve all data (process left subtree then right subtree)
            void InOrderTraversal(BSTNode^ node, System::Collections::Generic::List<StudentInfo^>^% items)
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
        System::Windows::Forms::DataGridView^ studentGridView;
        System::ComponentModel::Container^ components;
        System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn4;
        System::Windows::Forms::DataGridViewButtonColumn^ Action;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn1;
        System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn2;
        System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn3;
        System::Windows::Forms::DataGridViewTextBoxColumn^ Year;
        System::Windows::Forms::DataGridViewButtonColumn^ Update;
        System::Windows::Forms::DataGridViewButtonColumn^ Delete;
        System::Windows::Forms::Button^ button1;
        System::Windows::Forms::RadioButton^ radioButton1;
        System::Windows::Forms::RadioButton^ radioButton2;
        System::Windows::Forms::RadioButton^ radioButton3;
        System::Windows::Forms::RadioButton^ radioButton4;

        // Local inventory data (BST)
        StudentBST^ studentBST = gcnew StudentBST();
#pragma endregion

#pragma region Windows Form Designer generated code
    public:
        void InitializeComponent(void)
        {
            System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
            System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
            this->searchAllButton = (gcnew System::Windows::Forms::Button());
            this->inputTextBox = (gcnew System::Windows::Forms::TextBox());
            this->studentGridView = (gcnew System::Windows::Forms::DataGridView());
            this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->Year = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->Update = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
            this->Delete = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
            this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
            this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
            this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
            this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->studentGridView))->BeginInit();
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
            this->inputTextBox->Location = System::Drawing::Point(195, 26);
            this->inputTextBox->Name = L"inputTextBox";
            this->inputTextBox->Size = System::Drawing::Size(283, 20);
            this->inputTextBox->TabIndex = 1;
            // 
            // studentGridView
            // 
            this->studentGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->studentGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {
                this->dataGridViewTextBoxColumn1,
                    this->dataGridViewTextBoxColumn2, this->dataGridViewTextBoxColumn3, this->Year, this->Update, this->Delete
            });
            this->studentGridView->Location = System::Drawing::Point(20, 79);
            this->studentGridView->Name = L"studentGridView";
            this->studentGridView->Size = System::Drawing::Size(800, 537);
            this->studentGridView->TabIndex = 2;
            this->studentGridView->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::StudentGridView_CellContentClick);
            // 
            // dataGridViewTextBoxColumn1
            // 
            this->dataGridViewTextBoxColumn1->HeaderText = L"Student Id";
            this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
            // 
            // dataGridViewTextBoxColumn2
            // 
            this->dataGridViewTextBoxColumn2->HeaderText = L"Student Name";
            this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
            // 
            // dataGridViewTextBoxColumn3
            // 
            this->dataGridViewTextBoxColumn3->HeaderText = L"Course";
            this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
            // 
            // Year
            // 
            this->Year->HeaderText = L"Year";
            this->Year->Name = L"Year";
            // 
            // Update
            // 
            dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
            dataGridViewCellStyle1->NullValue = L"Update";
            this->Update->DefaultCellStyle = dataGridViewCellStyle1;
            this->Update->HeaderText = L"Update";
            this->Update->Name = L"Update";
            this->Update->Text = L"Update";
            this->Update->ToolTipText = L"Update";
            // 
            // Delete
            // 
            dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
            dataGridViewCellStyle2->NullValue = L"Delete";
            this->Delete->DefaultCellStyle = dataGridViewCellStyle2;
            this->Delete->HeaderText = L"Delete";
            this->Delete->Name = L"Delete";
            this->Delete->Text = L"Delete";
            this->Delete->ToolTipText = L"Delete";
            // 
            // dataGridViewTextBoxColumn4
            // 
            this->dataGridViewTextBoxColumn4->HeaderText = L"Year";
            this->dataGridViewTextBoxColumn4->Name = L"dataGridViewTextBoxColumn4";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(126, 29);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(56, 13);
            this->label1->TabIndex = 3;
            this->label1->Text = L"Student Id";
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(730, 27);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(90, 23);
            this->button1->TabIndex = 4;
            this->button1->Text = L"Reset";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
            // 
            // radioButton1
            // 
            this->radioButton1->AutoSize = true;
            this->radioButton1->Checked = true;
            this->radioButton1->Location = System::Drawing::Point(20, 56);
            this->radioButton1->Name = L"radioButton1";
            this->radioButton1->Size = System::Drawing::Size(70, 17);
            this->radioButton1->TabIndex = 5;
            this->radioButton1->TabStop = true;
            this->radioButton1->Text = L"10 record";
            this->radioButton1->UseVisualStyleBackColor = true;
            this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton1_CheckedChanged);
            // 
            // radioButton2
            // 
            this->radioButton2->AutoSize = true;
            this->radioButton2->Location = System::Drawing::Point(111, 56);
            this->radioButton2->Name = L"radioButton2";
            this->radioButton2->Size = System::Drawing::Size(76, 17);
            this->radioButton2->TabIndex = 6;
            this->radioButton2->Text = L"100 record";
            this->radioButton2->UseVisualStyleBackColor = true;
            this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton2_CheckedChanged);
            // 
            // radioButton3
            // 
            this->radioButton3->AutoSize = true;
            this->radioButton3->Location = System::Drawing::Point(202, 56);
            this->radioButton3->Name = L"radioButton3";
            this->radioButton3->Size = System::Drawing::Size(82, 17);
            this->radioButton3->TabIndex = 7;
            this->radioButton3->Text = L"1000 record";
            this->radioButton3->UseVisualStyleBackColor = true;
            this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton3_CheckedChanged);
            // 
            // radioButton4
            // 
            this->radioButton4->AutoSize = true;
            this->radioButton4->Location = System::Drawing::Point(293, 56);
            this->radioButton4->Name = L"radioButton4";
            this->radioButton4->Size = System::Drawing::Size(88, 17);
            this->radioButton4->TabIndex = 8;
            this->radioButton4->Text = L"10000 record";
            this->radioButton4->UseVisualStyleBackColor = true;
            this->radioButton4->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton4_CheckedChanged);
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(857, 628);
            this->Controls->Add(this->radioButton4);
            this->Controls->Add(this->radioButton3);
            this->Controls->Add(this->radioButton2);
            this->Controls->Add(this->radioButton1);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->searchAllButton);
            this->Controls->Add(this->inputTextBox);
            this->Controls->Add(this->studentGridView);
            this->Name = L"MyForm";
            this->Text = L"Student Management";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->studentGridView))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
#pragma region Load From Json
        // Load data from JSON file into BST
        void LoadDataFromJson()
        {
            studentBST = gcnew StudentBST();
            String^ json = fileName;
            // Convert to native std::string
            std::string nativeFileName = msclr::interop::marshal_as<std::string>(json);
            std::ifstream file(nativeFileName);

            if (!file.is_open())
            {
                MessageBox::Show("Unable to open JSON file.");
                return;
            }

            nlohmann::json jsonData;
            file >> jsonData;

            for (const auto& Info : jsonData)
            {
                int id = Info["studentId"];
                String^ name = gcnew String(Info["name"].get<std::string>().c_str());
                String^ course = gcnew String(Info["course"].get<std::string>().c_str());
                int year = Info["year"];

                StudentInfo^ newInfo = gcnew StudentInfo(id, name, course, year);
                studentBST->Insert(newInfo);
                newInfo = nullptr;
            }
            file.close();
        }

        // Populate DataGridView by traversing BST in order
        void PopulateGridView()
        {
            System::Collections::Generic::List<StudentInfo^>^ studentList = gcnew System::Collections::Generic::List<StudentInfo^>();
            System::Diagnostics::Stopwatch^ stopwatch = System::Diagnostics::Stopwatch::StartNew();

            studentBST->InOrderTraversal(studentBST->Root, studentList);

            stopwatch->Stop();
            String^ elapsedTime = String::Format("Search All Operation completed in {0} ticks (1 milliseconds = 1000 ticks).", (double)stopwatch->ElapsedTicks);

            this->studentGridView->Rows->Clear();
            for each (StudentInfo ^ student in studentList)
            {
                this->studentGridView->Rows->Add(student->StudentId, student->Name, student->Course, student->Year);
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
                    StudentInfo^ student = studentBST->Search(searchId);

                    stopwatch->Stop();
                    String^ elapsedTime = String::Format("Search Operation completed in {0} ticks (1 milliseconds = 1000 ticks).", stopwatch->ElapsedTicks);

                    if (student != nullptr)
                    {
                        // Display search result in the DataGridView
                        studentGridView->Rows->Clear();
                        studentGridView->Rows->Add(student->StudentId, student->Name, student->Course, student->Year);
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
        void StudentGridView_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0)
            {
                switch (e->ColumnIndex)
                {
                case 4: // Update button column
                {
                    int StudentId = Convert::ToInt32(this->studentGridView->Rows[e->RowIndex]->Cells[0]->Value);
                    String^ name = this->studentGridView->Rows[e->RowIndex]->Cells[1]->Value->ToString();
                    String^ course = this->studentGridView->Rows[e->RowIndex]->Cells[2]->Value->ToString();
                    int year = Convert::ToInt32(this->studentGridView->Rows[e->RowIndex]->Cells[3]->Value);

                    // Update the inventory
                    UpdateStudentData(StudentId, name, course, year);
                    break;
                }
                case 5: // Delete button column
                {
                    int inventoryId = Convert::ToInt32(this->studentGridView->Rows[e->RowIndex]->Cells[0]->Value);
                    DeleteInventoryData(inventoryId);
                    break;
                }
                }
            }
        }

        // Update inventory data in the BST
        void UpdateStudentData(int studentId, String^ name, String^ course, int year)
        {
            // Check if inventoryId is 0, in which case we perform an insert
            StudentInfo^ student = studentBST->Search(studentId);

            if (student == nullptr)
            {
                // Random number generation
                //std::random_device rd;
                //std::mt19937 gen(rd());
                //std::uniform_int_distribution<> distrib(1000000, 9999999); // 7-digit range

                //// Generate a random number
                //int randomNumber = distrib(gen);
                //studentId = randomNumber;

                // Create a new InventoryItem with the new studentId
                StudentInfo^ student = gcnew StudentInfo(studentId, name, course, year);

                System::Diagnostics::Stopwatch^ stopwatch = System::Diagnostics::Stopwatch::StartNew();
                // Insert the new item into the BST
                studentBST->Insert(student);

                stopwatch->Stop();
                String^ elapsedTime = String::Format("Insert Operation completed in {0} ticks (1 milliseconds = 1000 ticks).", stopwatch->ElapsedTicks);

                MessageBox::Show("New inventory item ( id: "+ studentId +") inserted successfully!\n" + elapsedTime);
                //PopulateGridView();
            }
            else {
                System::Diagnostics::Stopwatch^ stopwatch = System::Diagnostics::Stopwatch::StartNew();

                StudentInfo^ student = studentBST->Search(studentId);
                if (student != nullptr)
                {

                    student->Name = name;
                    student->Course = course;
                    student->Year = year;

                    stopwatch->Stop();
                    String^ elapsedTime = String::Format("Update Operation completed in {0} ticks (1 milliseconds = 1000 ticks).", stopwatch->ElapsedTicks);

                    MessageBox::Show("Inventory (id: "+ studentId +") updated successfully!\n" + elapsedTime);
                    //PopulateGridView();
                }
                else
                {
                    stopwatch->Stop();
                    MessageBox::Show("Item not found for update.");
                }
            }
        }

        // Delete inventory data from the BST
        void DeleteInventoryData(int studentId)
        {
            System::Diagnostics::Stopwatch^ stopwatch = System::Diagnostics::Stopwatch::StartNew();

            studentBST->Delete(studentId);

            stopwatch->Stop();
            String^ elapsedTime = String::Format("Delete Operation completed in {0} ticks (1 milliseconds = 1000 ticks).", stopwatch->ElapsedTicks);

            MessageBox::Show("Inventory (id: "+ studentId +") deleted successfully!\n" + elapsedTime);
            //PopulateGridView();
        }
#pragma endregion
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
    LoadDataFromJson();
    PopulateGridView();
}
private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    if (radioButton1->Checked) {
        fileName = "student_data10.json";
    }
}
private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    if (radioButton2->Checked) {
        fileName = "student_data100.json";
    }
}
private: System::Void radioButton3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    if (radioButton3->Checked) {
            fileName = "student_data1000.json";
    }
}
private: System::Void radioButton4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    if (radioButton4->Checked) {
        fileName = "student_data10000.json";
    }
}
};
}
