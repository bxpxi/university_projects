
namespace Lab2
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGrid_Parent = new System.Windows.Forms.DataGridView();
            this.dataGrid_Child = new System.Windows.Forms.DataGridView();
            this.tableName_Parent = new System.Windows.Forms.Label();
            this.tableName_Child = new System.Windows.Forms.Label();
            this.messageToUser = new System.Windows.Forms.Label();
            this.panel_Parent = new System.Windows.Forms.Panel();
            this.panel_Child = new System.Windows.Forms.Panel();
            this.addButton = new System.Windows.Forms.Button();
            this.updateButton = new System.Windows.Forms.Button();
            this.deleteButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_Parent)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_Child)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGrid_Parent
            // 
            this.dataGrid_Parent.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGrid_Parent.Location = new System.Drawing.Point(32, 68);
            this.dataGrid_Parent.Name = "dataGrid_Parent";
            this.dataGrid_Parent.RowHeadersWidth = 62;
            this.dataGrid_Parent.RowTemplate.Height = 28;
            this.dataGrid_Parent.Size = new System.Drawing.Size(636, 268);
            this.dataGrid_Parent.TabIndex = 0;
            this.dataGrid_Parent.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGrid_Parent_CellClick);
            // 
            // dataGrid_Child
            // 
            this.dataGrid_Child.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGrid_Child.Location = new System.Drawing.Point(40, 398);
            this.dataGrid_Child.Name = "dataGrid_Child";
            this.dataGrid_Child.RowHeadersWidth = 62;
            this.dataGrid_Child.RowTemplate.Height = 28;
            this.dataGrid_Child.Size = new System.Drawing.Size(861, 260);
            this.dataGrid_Child.TabIndex = 1;
            this.dataGrid_Child.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGrid_Child_CellClick);
            // 
            // tableName_Parent
            // 
            this.tableName_Parent.AutoSize = true;
            this.tableName_Parent.Location = new System.Drawing.Point(50, 30);
            this.tableName_Parent.Name = "tableName_Parent";
            this.tableName_Parent.Size = new System.Drawing.Size(56, 20);
            this.tableName_Parent.TabIndex = 2;
            this.tableName_Parent.Text = "Parent";
            // 
            // tableName_Child
            // 
            this.tableName_Child.AutoSize = true;
            this.tableName_Child.Location = new System.Drawing.Point(62, 360);
            this.tableName_Child.Name = "tableName_Child";
            this.tableName_Child.Size = new System.Drawing.Size(44, 20);
            this.tableName_Child.TabIndex = 3;
            this.tableName_Child.Text = "Child";
            // 
            // messageToUser
            // 
            this.messageToUser.AutoSize = true;
            this.messageToUser.Location = new System.Drawing.Point(837, 30);
            this.messageToUser.Name = "messageToUser";
            this.messageToUser.Size = new System.Drawing.Size(51, 20);
            this.messageToUser.TabIndex = 4;
            this.messageToUser.Text = "label3";
            // 
            // panel_Parent
            // 
            this.panel_Parent.BackColor = System.Drawing.SystemColors.ControlLight;
            this.panel_Parent.Location = new System.Drawing.Point(773, 78);
            this.panel_Parent.Name = "panel_Parent";
            this.panel_Parent.Size = new System.Drawing.Size(469, 232);
            this.panel_Parent.TabIndex = 5;
            // 
            // panel_Child
            // 
            this.panel_Child.BackColor = System.Drawing.SystemColors.ControlLight;
            this.panel_Child.Location = new System.Drawing.Point(968, 394);
            this.panel_Child.Name = "panel_Child";
            this.panel_Child.Size = new System.Drawing.Size(367, 350);
            this.panel_Child.TabIndex = 6;
            // 
            // addButton
            // 
            this.addButton.Location = new System.Drawing.Point(1316, 88);
            this.addButton.Name = "addButton";
            this.addButton.Size = new System.Drawing.Size(89, 32);
            this.addButton.TabIndex = 7;
            this.addButton.Text = "ADD";
            this.addButton.UseVisualStyleBackColor = true;
            this.addButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // updateButton
            // 
            this.updateButton.Location = new System.Drawing.Point(1316, 162);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(89, 31);
            this.updateButton.TabIndex = 8;
            this.updateButton.Text = "UPDATE";
            this.updateButton.UseVisualStyleBackColor = true;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // deleteButton
            // 
            this.deleteButton.Location = new System.Drawing.Point(1316, 230);
            this.deleteButton.Name = "deleteButton";
            this.deleteButton.Size = new System.Drawing.Size(89, 34);
            this.deleteButton.TabIndex = 9;
            this.deleteButton.Text = "DELETE";
            this.deleteButton.UseVisualStyleBackColor = true;
            this.deleteButton.Click += new System.EventHandler(this.deleteButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1486, 670);
            this.Controls.Add(this.deleteButton);
            this.Controls.Add(this.updateButton);
            this.Controls.Add(this.addButton);
            this.Controls.Add(this.panel_Child);
            this.Controls.Add(this.panel_Parent);
            this.Controls.Add(this.messageToUser);
            this.Controls.Add(this.tableName_Child);
            this.Controls.Add(this.tableName_Parent);
            this.Controls.Add(this.dataGrid_Child);
            this.Controls.Add(this.dataGrid_Parent);
            this.Name = "Form1";
            this.Text = "Clinica Medicala";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_Parent)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGrid_Child)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGrid_Parent;
        private System.Windows.Forms.DataGridView dataGrid_Child;
        private System.Windows.Forms.Label tableName_Parent;
        private System.Windows.Forms.Label tableName_Child;
        private System.Windows.Forms.Label messageToUser;
        private System.Windows.Forms.Panel panel_Parent;
        private System.Windows.Forms.Panel panel_Child;
        private System.Windows.Forms.Button addButton;
        private System.Windows.Forms.Button updateButton;
        private System.Windows.Forms.Button deleteButton;
    }
}

