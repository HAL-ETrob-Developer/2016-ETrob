using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EV3RT_2016_FORM
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void createSW_Click(object sender, EventArgs e)
        {
            string strSpdP = textBoxSpdP.Text;
            string strSpdI = textBoxSpdI.Text;
            string strSpdD = textBoxSpdD.Text;
            string strDegP = textBoxDegP.Text;
            string strDegI = textBoxDegI.Text;
            string strDegD = textBoxDegD.Text;

            PID_SETTING pidSetFile;
            pidSetFile.fSpdP = 0.0F;
            pidSetFile.fSpdI = 0.0F;
            pidSetFile.fSpdD = 0.0F;
            pidSetFile.fDegP = 0.0F;
            pidSetFile.fDegI = 0.0F;
            pidSetFile.fDegD = 0.0F;


            if ( strSpdP != "" ) { pidSetFile.fSpdP = float.Parse( strSpdP ); }
            if ( strSpdI != "" ) { pidSetFile.fSpdI = float.Parse( strSpdI ); }
            if ( strSpdD != "" ) { pidSetFile.fSpdD = float.Parse( strSpdD ); }
            if ( strDegP != "" ) { pidSetFile.fDegP = float.Parse( strDegP ); }
            if ( strDegI != "" ) { pidSetFile.fDegI = float.Parse( strDegI ); }
            if ( strDegD != "" ) { pidSetFile.fDegD = float.Parse( strDegD ); }

            unsafe
            {
                //File.Create(@"test\binary");

                // バイナリ形式でファイルに書き出し。
                using (BinaryWriter w = new BinaryWriter(File.Create(@"pid_settings")))
                {
                    //w.Write(new byte[] { (byte)0x01, (byte)0x23, (byte)0x45, (byte)0x67, });

                    int i = 0;
                    char[] pidSetFileByte = new char[26];

                    for( i = 0; i < 26; i++ ) {
                        pidSetFileByte[i] = *(((char*)(&pidSetFile)) + i );
                    }

                    //w.Write(pidSetFileByte);

                    w.Write(pidSetFile.fSpdP);
                    w.Write(pidSetFile.fSpdI);
                    w.Write(pidSetFile.fSpdD);
                    w.Write(pidSetFile.fDegP);
                    w.Write(pidSetFile.fDegI);
                    w.Write(pidSetFile.fDegD);
                }
            }

            this.Close();
        }
    }

    struct PID_SETTING{
        public float fSpdP;
        public float fSpdI;
        public float fSpdD;
        public float fDegP;
        public float fDegI;
        public float fDegD;
    };
}
