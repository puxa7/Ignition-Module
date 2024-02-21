using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;

namespace Trening
{
    public partial class a : Form
    {
        public delegate void d1(string indata);

        string duzy;
        delegate void serialCalback(string val); // pomost pomiedzy watkami*/
        bool warunek = false;
        string[] katy1 = new string[10];
        string[] katy2 = new string[10];
        string[] katy3 = new string[10];
        string[] katy4 = new string[10];
        string[] katy5 = new string[10];

        
        
        public a()
        {
            
            InitializeComponent();
            chart1.Titles.Add("BTDC");
            disableControls();

            // trzy linijki poniżej żeby się kratki na wkresie pojawiły na początku
            chart1.Series["BTDC"].Points.Clear();
            chart1.Series["BTDC"].BorderWidth = 3;
            chart1.Series["BTDC"].Points.AddXY("0", 0);
        }
     

        private void onButton_Click(object sender, EventArgs e)
        {
            
        }

        private void offButton_Click(object sender, EventArgs e)
        {
            
        }

        private void servoAngle_Click(object sender, EventArgs e)
        {

        }
        private void a_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.Write("!o");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            warunek = true;           
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label12_Click(object sender, EventArgs e)
        {

        }

        private void button5_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            Array.Clear(katy1, 0, katy1.Length);
            Array.Clear(katy2, 0, katy1.Length);
            Array.Clear(katy3, 0, katy1.Length);
            Array.Clear(katy4, 0, katy1.Length);
            Array.Clear(katy5, 0, katy1.Length);
            chart1.Series["BTDC"].Points.Clear();
            // dwie linijki poniżej żeby się kratki na wkresie pojawiły na początku
            
            chart1.Series["BTDC"].BorderWidth = 3;
            chart1.Series["BTDC"].Points.AddXY("0", 0);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            string doWysylki="<";
            for(int i=0;i<10;i++)
            {
                doWysylki += katy1[i];
                if (i < 9)
                {
                    doWysylki += ",";
                } 
            }
            doWysylki += ";";

            
            for (int i = 0; i < 10; i++)
            {
                doWysylki += katy2[i];
                if (i < 9)
                {
                    doWysylki += ",";
                }
            }
            doWysylki += ";";

            for (int i = 0; i < 10; i++)
            {
                doWysylki += katy3[i];
                if (i < 9)
                {
                    doWysylki += ",";
                }
            }
            doWysylki += ";";

            for (int i = 0; i < 10; i++)
            {
                doWysylki += katy4[i];
                if (i < 9)
                {
                    doWysylki += ",";
                }
            }
            doWysylki += ";";

            for (int i = 0; i < 10; i++)
            {
                doWysylki += katy5[i];
                if (i < 9)
                {
                    doWysylki += ",";
                }
            }
            doWysylki += ";";

            doWysylki += ">";
            Console.WriteLine(doWysylki);
          
            try
            {
                serialPort1.Write(doWysylki);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }


       
        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            string indata = serialPort1.ReadLine();
            d1 writeit = new d1(Write2Form);
            Invoke(writeit, indata);
        }

        public void Write2Form(string indata)
        {
                duzy += indata;
                StreamWriter sw = new StreamWriter(Application.StartupPath + "\\datalog.txt");
                sw.WriteLine(duzy);
                sw.Close();
                warunek = false;
                Console.WriteLine("Koniec Write2Form");         

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.Open();
                    button7.Enabled = false;
                    button8.Enabled = true;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }
        

     

        private void resetDefaults()
        {
            textBox1.Text = "";
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void enableControls()
        {
           

        }

        private void disableControls()
        {

        }

        

        private void button3_Click(object sender, EventArgs e)
        {

            

            if(int.Parse(listBox1.Items.Count.ToString())==0)
            {
                katy1[0] = textBox1.Text;
                katy1[1] = textBox2.Text;
                katy1[2] = textBox3.Text;
                katy1[3] = textBox4.Text;
                katy1[4] = textBox5.Text;
                katy1[5] = textBox6.Text;
                katy1[6] = textBox7.Text;
                katy1[7] = textBox8.Text;
                katy1[8] = textBox9.Text;
                katy1[9] = textBox10.Text;

               
                if (katy1[0] != null)
                {
                    listBox1.Items.Add(katy1[0]);
                }
                chart1.Series["BTDC"].Points.Clear();
                chart1.Series["BTDC"].BorderWidth = 3;
                chart1.Series["BTDC"].Points.AddXY("0", katy1[1]);
                chart1.Series["BTDC"].Points.AddXY("1000", katy1[2]);
                chart1.Series["BTDC"].Points.AddXY("2000", katy1[3]);
                chart1.Series["BTDC"].Points.AddXY("3000", katy1[4]);
                chart1.Series["BTDC"].Points.AddXY("4000", katy1[5]);
                chart1.Series["BTDC"].Points.AddXY("5000", katy1[6]);
                chart1.Series["BTDC"].Points.AddXY("6000", katy1[7]);
                chart1.Series["BTDC"].Points.AddXY("7000", katy1[8]);
                chart1.Series["BTDC"].Points.AddXY("8000", katy1[9]);
                
            }
            else if(int.Parse(listBox1.Items.Count.ToString()) == 1)
            {

                katy2[0] = textBox1.Text;
                katy2[1] = textBox2.Text;
                katy2[2] = textBox3.Text;
                katy2[3] = textBox4.Text;
                katy2[4] = textBox5.Text;
                katy2[5] = textBox6.Text;
                katy2[6] = textBox7.Text;
                katy2[7] = textBox8.Text;
                katy2[8] = textBox9.Text;
                katy2[9] = textBox10.Text;

                if (katy2[0] != null)
                {
                    listBox1.Items.Add(katy2[0]);
                }

                
                chart1.Series["BTDC"].Points.Clear();
                chart1.Series["BTDC"].BorderWidth = 3;
                chart1.Series["BTDC"].Points.AddXY("0", katy2[1]);
                chart1.Series["BTDC"].Points.AddXY("1000", katy2[2]);
                chart1.Series["BTDC"].Points.AddXY("2000", katy2[3]);
                chart1.Series["BTDC"].Points.AddXY("3000", katy2[4]);
                chart1.Series["BTDC"].Points.AddXY("4000", katy2[5]);
                chart1.Series["BTDC"].Points.AddXY("5000", katy2[6]);
                chart1.Series["BTDC"].Points.AddXY("6000", katy2[7]);
                chart1.Series["BTDC"].Points.AddXY("7000", katy2[8]);
                chart1.Series["BTDC"].Points.AddXY("8000", katy2[9]);
            }
            else if (int.Parse(listBox1.Items.Count.ToString()) == 2)
            {

                katy3[0] = textBox1.Text;
                katy3[1] = textBox2.Text;
                katy3[2] = textBox3.Text;
                katy3[3] = textBox4.Text;
                katy3[4] = textBox5.Text;
                katy3[5] = textBox6.Text;
                katy3[6] = textBox7.Text;
                katy3[7] = textBox8.Text;
                katy3[8] = textBox9.Text;
                katy3[9] = textBox10.Text;

                if (katy3[0] != null)
                {
                    listBox1.Items.Add(katy3[0]);
                }

                
                chart1.Series["BTDC"].Points.Clear();
                chart1.Series["BTDC"].BorderWidth = 3;
                chart1.Series["BTDC"].Points.AddXY("0", katy3[1]);
                chart1.Series["BTDC"].Points.AddXY("1000", katy3[2]);
                chart1.Series["BTDC"].Points.AddXY("2000", katy3[3]);
                chart1.Series["BTDC"].Points.AddXY("3000", katy3[4]);
                chart1.Series["BTDC"].Points.AddXY("4000", katy3[5]);
                chart1.Series["BTDC"].Points.AddXY("5000", katy3[6]);
                chart1.Series["BTDC"].Points.AddXY("6000", katy3[7]);
                chart1.Series["BTDC"].Points.AddXY("7000", katy3[8]);
                chart1.Series["BTDC"].Points.AddXY("8000", katy3[9]);
            }

            else if (int.Parse(listBox1.Items.Count.ToString()) == 3)
            {

                katy4[0] = textBox1.Text;
                katy4[1] = textBox2.Text;
                katy4[2] = textBox3.Text;
                katy4[3] = textBox4.Text;
                katy4[4] = textBox5.Text;
                katy4[5] = textBox6.Text;
                katy4[6] = textBox7.Text;
                katy4[7] = textBox8.Text;
                katy4[8] = textBox9.Text;
                katy4[9] = textBox10.Text;

                if (katy4[0] != null)
                {
                    listBox1.Items.Add(katy4[0]);
                }

                
                chart1.Series["BTDC"].Points.Clear();
                chart1.Series["BTDC"].BorderWidth = 3;
                chart1.Series["BTDC"].Points.AddXY("0", katy4[1]);
                chart1.Series["BTDC"].Points.AddXY("1000", katy4[2]);
                chart1.Series["BTDC"].Points.AddXY("2000", katy4[3]);
                chart1.Series["BTDC"].Points.AddXY("3000", katy4[4]);
                chart1.Series["BTDC"].Points.AddXY("4000", katy4[5]);
                chart1.Series["BTDC"].Points.AddXY("5000", katy4[6]);
                chart1.Series["BTDC"].Points.AddXY("6000", katy4[7]);
                chart1.Series["BTDC"].Points.AddXY("7000", katy4[8]);
                chart1.Series["BTDC"].Points.AddXY("8000", katy4[9]);
            }

            else if (int.Parse(listBox1.Items.Count.ToString()) == 4)
            {

                katy5[0] = textBox1.Text;
                katy5[1] = textBox2.Text;
                katy5[2] = textBox3.Text;
                katy5[3] = textBox4.Text;
                katy5[4] = textBox5.Text;
                katy5[5] = textBox6.Text;
                katy5[6] = textBox7.Text;
                katy5[7] = textBox8.Text;
                katy5[8] = textBox9.Text;
                katy5[9] = textBox10.Text;

                if (katy5[0] != null)
                {
                    listBox1.Items.Add(katy5[0]);
                }

                
                chart1.Series["BTDC"].Points.Clear(); 
                chart1.Series["BTDC"].BorderWidth = 3;
                chart1.Series["BTDC"].Points.AddXY("0", katy5[1]);
                chart1.Series["BTDC"].Points.AddXY("1000", katy5[2]);
                chart1.Series["BTDC"].Points.AddXY("2000", katy5[3]);
                chart1.Series["BTDC"].Points.AddXY("3000", katy5[4]);
                chart1.Series["BTDC"].Points.AddXY("4000", katy5[5]);
                chart1.Series["BTDC"].Points.AddXY("5000", katy5[6]);
                chart1.Series["BTDC"].Points.AddXY("6000", katy5[7]);
                chart1.Series["BTDC"].Points.AddXY("7000", katy5[8]);
                chart1.Series["BTDC"].Points.AddXY("8000", katy5[9]);
            }

        }

        private void wykres()
        {

        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void chart1_Click(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            try
               {
                    serialPort1.Write("#" + comboBox2.Text);
               }
               catch (Exception ex)
               {
                    MessageBox.Show(ex.Message);
               }
                Console.WriteLine("#" + comboBox2.Text);
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button8_Click(object sender, EventArgs e)
        {
            try
            {
                if (serialPort1.IsOpen)
                {
                    serialPort1.Close();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            button7.Enabled = true;
            button8.Enabled = false;
        }

        private void textBox11_TextChanged(object sender, EventArgs e)
        {

        }
    }

}
