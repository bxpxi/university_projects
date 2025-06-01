using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab1_sper_ultim
{
    public partial class Form1 : Form
    {
        string connectionString = @"Server=Patricia\SQLEXPRESS;Database=ClinicaMedicala;
        Integrated Security=true;TrustServerCertificate=true;";
        DataSet ds = new DataSet();
        SqlDataAdapter parentAdapter = new SqlDataAdapter();
        SqlDataAdapter childAdapter = new SqlDataAdapter();
        BindingSource parentBS = new BindingSource();
        BindingSource childBS = new BindingSource();

        private int specializareSelectata = 0;
        private int medicSelectat = 0;
        private string numeMedic;
        private string prenumeMedic;
        private string emailMedic;
        private string telefonMedic;
        private string gradMedic;

        public Form1()
        {
            InitializeComponent();
        }

        public void refreshDataGridView()
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();

                    parentAdapter.SelectCommand = new SqlCommand("SELECT * FROM Specializari;",
                        connection);
                    childAdapter.SelectCommand = new SqlCommand("SELECT * FROM Medici;",
                        connection);
                    ds.Clear();
                    parentAdapter.Fill(ds, "Specializari");
                    childAdapter.Fill(ds, "Medici");
                    parentBS.DataSource = ds.Tables["Specializari"];
                    dataGridViewParent.DataSource = parentBS;
                    dataGridViewChild.DataSource = childBS;

                    connection.Close();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void dataGridViewParent_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0 && e.ColumnIndex >= 0)
            {
                DataGridViewRow row = dataGridViewParent.Rows[e.RowIndex];
                int.TryParse(row.Cells[0].Value.ToString(), out specializareSelectata);
            }
            txtNume.Text = "";
            txtPrenume.Text = "";
            txtEmail.Text = "";
            txtTelefon.Text = "";
            txtGrad.Text = "";
        }

        private void dataGridViewChild_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0 && e.ColumnIndex >= 0)
            {
                DataGridViewRow row = dataGridViewChild.Rows[e.RowIndex];
                int.TryParse(row.Cells[0].Value.ToString(), out medicSelectat);
                numeMedic = row.Cells[1].Value.ToString();
                prenumeMedic = row.Cells[2].Value.ToString();
                emailMedic = row.Cells[5].Value.ToString();
                telefonMedic = row.Cells[4].Value.ToString();
                gradMedic = row.Cells[7].Value.ToString();
            }
            txtNume.Text = numeMedic;
            txtPrenume.Text = prenumeMedic;
            txtEmail.Text = emailMedic;
            txtTelefon.Text = telefonMedic;
            txtGrad.Text = gradMedic;
        }

        private void txtPrenume_TextChanged(object sender, EventArgs e)
        {

        }

        private void btnAdaugaMedic_Click(object sender, EventArgs e)
        {
            if (specializareSelectata == 0)
            {
                MessageBox.Show("Alegeti o specializare pentru medic.");
            }
            else
            {
                try
                {
                    using (SqlConnection connection = new SqlConnection(connectionString))
                    {
                        connection.Open();
                        SqlCommand insertCommand = new SqlCommand("INSERT INTO Medici(Nume, Prenume, ID_specializare," +
                                   "Email, Telefon, Data_angajarii, Grad_profesional) VALUES (@nume, @prenume, @id_specializare, @email, @telefon, @data, @grad);", connection);
                        insertCommand.Parameters.AddWithValue("@nume", txtNume.Text);
                        insertCommand.Parameters.AddWithValue("@prenume", txtPrenume.Text);
                        insertCommand.Parameters.AddWithValue("@id_specializare", specializareSelectata);
                        insertCommand.Parameters.AddWithValue("@email", txtEmail.Text);
                        insertCommand.Parameters.AddWithValue("@telefon", txtTelefon.Text);
                        insertCommand.Parameters.AddWithValue("@data", DateTime.Now);
                        insertCommand.Parameters.AddWithValue("@grad", txtGrad.Text);
                        MessageBox.Show($"Valoarea selectată este: {specializareSelectata}");
                        int inserRowCount = insertCommand.ExecuteNonQuery();
                        MessageBox.Show("Medicul a fost adaugat cu succes!");
                        txtNume.Text = "";
                        txtPrenume.Text = "";
                        txtEmail.Text = "";
                        txtTelefon.Text = "";
                        txtGrad.Text = "";
                        refreshDataGridView();
                        connection.Close();
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void btnStergeMedic_Click(object sender, EventArgs e)
        {
            if (medicSelectat == 0)
            {
                MessageBox.Show("Alegeti un medic.");
            }
            else
            {
                try
                {
                    using (SqlConnection connection = new SqlConnection(connectionString))
                    {
                        connection.Open();
                        SqlCommand deleteCommand = new SqlCommand("DELETE FROM Medici WHERE ID_medic=@id;", connection);
                        deleteCommand.Parameters.AddWithValue("@id", medicSelectat);
                        int deleteRowCount = deleteCommand.ExecuteNonQuery();
                        MessageBox.Show("Medicul a fost sters cu succes!");
                        txtNume.Text = "";
                        txtPrenume.Text = "";
                        txtEmail.Text = "";
                        txtTelefon.Text = "";
                        txtGrad.Text = "";
                        refreshDataGridView();
                        connection.Close();
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void btnActualizeazaMedic_Click(object sender, EventArgs e)
        {
            if (medicSelectat == 0)
            {
                MessageBox.Show("Alegeti un medic.");
            }
            else
            {
                try
                {
                    using (SqlConnection connection = new SqlConnection(connectionString))
                    {
                        connection.Open();
                        SqlCommand updateCommand = new SqlCommand("UPDATE Medici SET Nume=@nume, Prenume=@prenume, Email=@email, Telefon=@telefon, Grad_profesional=@grad WHERE ID_medic=@id;", connection);
                        updateCommand.Parameters.AddWithValue("@nume", txtNume.Text);
                        updateCommand.Parameters.AddWithValue("@prenume", txtPrenume.Text);
                        updateCommand.Parameters.AddWithValue("@email", txtEmail.Text);
                        updateCommand.Parameters.AddWithValue("@telefon", txtTelefon.Text);
                        updateCommand.Parameters.AddWithValue("@grad", txtGrad.Text);
                        updateCommand.Parameters.AddWithValue("@id", medicSelectat);
                        int updateRowCount = updateCommand.ExecuteNonQuery();
                        MessageBox.Show("Medicul a fost actualizat cu succes!");
                        txtNume.Text = "";
                        txtPrenume.Text = "";
                        txtEmail.Text = "";
                        txtTelefon.Text = "";
                        txtGrad.Text = "";
                        refreshDataGridView();
                        connection.Close();
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();

                    parentAdapter.SelectCommand = new SqlCommand("SELECT * FROM Specializari;",
                        connection);
                    childAdapter.SelectCommand = new SqlCommand("SELECT * FROM Medici;",
                        connection);
                    parentAdapter.Fill(ds, "Specializari");
                    childAdapter.Fill(ds, "Medici");
                    parentBS.DataSource = ds.Tables["Specializari"];
                    dataGridViewParent.DataSource = parentBS;
                    DataColumn parentColumn = ds.Tables["Specializari"].Columns["ID_specializare"];
                    DataColumn childColumn = ds.Tables["Medici"].Columns["ID_specializare"];
                    DataRelation relation = new DataRelation("FK_Specializari_Medici",
                        parentColumn, childColumn);
                    ds.Relations.Add(relation);
                    childBS.DataSource = parentBS;
                    childBS.DataMember = "FK_Specializari_Medici";
                    dataGridViewChild.DataSource = childBS;

                    connection.Close();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
