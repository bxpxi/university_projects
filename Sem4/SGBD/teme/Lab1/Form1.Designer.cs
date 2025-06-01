
namespace Lab1_sper_ultim
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
            this.dataGridViewParent = new System.Windows.Forms.DataGridView();
            this.dataGridViewChild = new System.Windows.Forms.DataGridView();
            this.lblNume = new System.Windows.Forms.Label();
            this.lblPrenume = new System.Windows.Forms.Label();
            this.lblEmail = new System.Windows.Forms.Label();
            this.lblTelefon = new System.Windows.Forms.Label();
            this.lblGrad = new System.Windows.Forms.Label();
            this.txtNume = new System.Windows.Forms.TextBox();
            this.txtPrenume = new System.Windows.Forms.TextBox();
            this.txtEmail = new System.Windows.Forms.TextBox();
            this.txtTelefon = new System.Windows.Forms.TextBox();
            this.txtGrad = new System.Windows.Forms.TextBox();
            this.btnAdaugaMedic = new System.Windows.Forms.Button();
            this.btnActualizeazaMedic = new System.Windows.Forms.Button();
            this.btnStergeMedic = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewParent)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewChild)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewParent
            // 
            this.dataGridViewParent.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewParent.Location = new System.Drawing.Point(27, 73);
            this.dataGridViewParent.Name = "dataGridViewParent";
            this.dataGridViewParent.RowHeadersWidth = 62;
            this.dataGridViewParent.RowTemplate.Height = 28;
            this.dataGridViewParent.Size = new System.Drawing.Size(490, 423);
            this.dataGridViewParent.TabIndex = 0;
            this.dataGridViewParent.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridViewParent_CellClick);
            // 
            // dataGridViewChild
            // 
            this.dataGridViewChild.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewChild.Location = new System.Drawing.Point(568, 71);
            this.dataGridViewChild.Name = "dataGridViewChild";
            this.dataGridViewChild.RowHeadersWidth = 62;
            this.dataGridViewChild.RowTemplate.Height = 28;
            this.dataGridViewChild.Size = new System.Drawing.Size(466, 425);
            this.dataGridViewChild.TabIndex = 1;
            this.dataGridViewChild.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridViewChild_CellClick);
            // 
            // lblNume
            // 
            this.lblNume.AutoSize = true;
            this.lblNume.Location = new System.Drawing.Point(1076, 76);
            this.lblNume.Name = "lblNume";
            this.lblNume.Size = new System.Drawing.Size(55, 20);
            this.lblNume.TabIndex = 2;
            this.lblNume.Text = "Nume:";
            // 
            // lblPrenume
            // 
            this.lblPrenume.AutoSize = true;
            this.lblPrenume.Location = new System.Drawing.Point(1076, 152);
            this.lblPrenume.Name = "lblPrenume";
            this.lblPrenume.Size = new System.Drawing.Size(77, 20);
            this.lblPrenume.TabIndex = 3;
            this.lblPrenume.Text = "Prenume:";
            // 
            // lblEmail
            // 
            this.lblEmail.AutoSize = true;
            this.lblEmail.Location = new System.Drawing.Point(1079, 220);
            this.lblEmail.Name = "lblEmail";
            this.lblEmail.Size = new System.Drawing.Size(52, 20);
            this.lblEmail.TabIndex = 4;
            this.lblEmail.Text = "Email:";
            // 
            // lblTelefon
            // 
            this.lblTelefon.AutoSize = true;
            this.lblTelefon.Location = new System.Drawing.Point(1079, 280);
            this.lblTelefon.Name = "lblTelefon";
            this.lblTelefon.Size = new System.Drawing.Size(66, 20);
            this.lblTelefon.TabIndex = 5;
            this.lblTelefon.Text = "Telefon:";
            // 
            // lblGrad
            // 
            this.lblGrad.AutoSize = true;
            this.lblGrad.Location = new System.Drawing.Point(1082, 340);
            this.lblGrad.Name = "lblGrad";
            this.lblGrad.Size = new System.Drawing.Size(49, 20);
            this.lblGrad.TabIndex = 6;
            this.lblGrad.Text = "Grad:";
            // 
            // txtNume
            // 
            this.txtNume.Location = new System.Drawing.Point(1165, 73);
            this.txtNume.Name = "txtNume";
            this.txtNume.Size = new System.Drawing.Size(168, 26);
            this.txtNume.TabIndex = 7;
            // 
            // txtPrenume
            // 
            this.txtPrenume.Location = new System.Drawing.Point(1165, 146);
            this.txtPrenume.Name = "txtPrenume";
            this.txtPrenume.Size = new System.Drawing.Size(168, 26);
            this.txtPrenume.TabIndex = 8;
            this.txtPrenume.TextChanged += new System.EventHandler(this.txtPrenume_TextChanged);
            // 
            // txtEmail
            // 
            this.txtEmail.Location = new System.Drawing.Point(1165, 214);
            this.txtEmail.Name = "txtEmail";
            this.txtEmail.Size = new System.Drawing.Size(168, 26);
            this.txtEmail.TabIndex = 9;
            // 
            // txtTelefon
            // 
            this.txtTelefon.Location = new System.Drawing.Point(1165, 274);
            this.txtTelefon.Name = "txtTelefon";
            this.txtTelefon.Size = new System.Drawing.Size(168, 26);
            this.txtTelefon.TabIndex = 10;
            // 
            // txtGrad
            // 
            this.txtGrad.Location = new System.Drawing.Point(1165, 337);
            this.txtGrad.Name = "txtGrad";
            this.txtGrad.Size = new System.Drawing.Size(168, 26);
            this.txtGrad.TabIndex = 11;
            // 
            // btnAdaugaMedic
            // 
            this.btnAdaugaMedic.Location = new System.Drawing.Point(1190, 440);
            this.btnAdaugaMedic.Name = "btnAdaugaMedic";
            this.btnAdaugaMedic.Size = new System.Drawing.Size(94, 30);
            this.btnAdaugaMedic.TabIndex = 12;
            this.btnAdaugaMedic.Text = "ADD";
            this.btnAdaugaMedic.UseVisualStyleBackColor = true;
            this.btnAdaugaMedic.Click += new System.EventHandler(this.btnAdaugaMedic_Click);
            // 
            // btnActualizeazaMedic
            // 
            this.btnActualizeazaMedic.Location = new System.Drawing.Point(1190, 501);
            this.btnActualizeazaMedic.Name = "btnActualizeazaMedic";
            this.btnActualizeazaMedic.Size = new System.Drawing.Size(94, 29);
            this.btnActualizeazaMedic.TabIndex = 13;
            this.btnActualizeazaMedic.Text = "UPDATE";
            this.btnActualizeazaMedic.UseVisualStyleBackColor = true;
            this.btnActualizeazaMedic.Click += new System.EventHandler(this.btnActualizeazaMedic_Click);
            // 
            // btnStergeMedic
            // 
            this.btnStergeMedic.Location = new System.Drawing.Point(1190, 564);
            this.btnStergeMedic.Name = "btnStergeMedic";
            this.btnStergeMedic.Size = new System.Drawing.Size(94, 32);
            this.btnStergeMedic.TabIndex = 14;
            this.btnStergeMedic.Text = "DELETE";
            this.btnStergeMedic.UseVisualStyleBackColor = true;
            this.btnStergeMedic.Click += new System.EventHandler(this.btnStergeMedic_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1377, 662);
            this.Controls.Add(this.btnStergeMedic);
            this.Controls.Add(this.btnActualizeazaMedic);
            this.Controls.Add(this.btnAdaugaMedic);
            this.Controls.Add(this.txtGrad);
            this.Controls.Add(this.txtTelefon);
            this.Controls.Add(this.txtEmail);
            this.Controls.Add(this.txtPrenume);
            this.Controls.Add(this.txtNume);
            this.Controls.Add(this.lblGrad);
            this.Controls.Add(this.lblTelefon);
            this.Controls.Add(this.lblEmail);
            this.Controls.Add(this.lblPrenume);
            this.Controls.Add(this.lblNume);
            this.Controls.Add(this.dataGridViewChild);
            this.Controls.Add(this.dataGridViewParent);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewParent)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewChild)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewParent;
        private System.Windows.Forms.DataGridView dataGridViewChild;
        private System.Windows.Forms.Label lblNume;
        private System.Windows.Forms.Label lblPrenume;
        private System.Windows.Forms.Label lblEmail;
        private System.Windows.Forms.Label lblTelefon;
        private System.Windows.Forms.Label lblGrad;
        private System.Windows.Forms.TextBox txtNume;
        private System.Windows.Forms.TextBox txtPrenume;
        private System.Windows.Forms.TextBox txtEmail;
        private System.Windows.Forms.TextBox txtTelefon;
        private System.Windows.Forms.TextBox txtGrad;
        private System.Windows.Forms.Button btnAdaugaMedic;
        private System.Windows.Forms.Button btnActualizeazaMedic;
        private System.Windows.Forms.Button btnStergeMedic;
    }
}

