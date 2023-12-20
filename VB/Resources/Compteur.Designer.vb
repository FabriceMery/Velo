<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class BlueSoft
    Inherits System.Windows.Forms.Form

    'Form remplace la méthode Dispose pour nettoyer la liste des composants.
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Requise par le Concepteur Windows Form
    Private components As System.ComponentModel.IContainer

    'REMARQUE : la procédure suivante est requise par le Concepteur Windows Form
    'Elle peut être modifiée à l'aide du Concepteur Windows Form.  
    'Ne la modifiez pas à l'aide de l'éditeur de code.
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.SerialPort1 = New System.IO.Ports.SerialPort(Me.components)
        Me.PictureBox1 = New System.Windows.Forms.PictureBox()
        Me.ListBox3 = New System.Windows.Forms.ListBox()
        Me.SerialPort2 = New System.IO.Ports.SerialPort(Me.components)
        Me.Label2 = New System.Windows.Forms.Label()
        Me.R_Moteur = New System.Windows.Forms.Button()
        Me.Angle2 = New System.Windows.Forms.Label()
        Me.Angle1 = New System.Windows.Forms.Label()
        Me.Magx = New System.Windows.Forms.Label()
        Me.Magy = New System.Windows.Forms.Label()
        Me.Timer4 = New System.Windows.Forms.Timer(Me.components)
        Me.ButtonAngle1 = New System.Windows.Forms.Button()
        Me.ButtonAbgle2 = New System.Windows.Forms.Button()
        Me.Mag = New System.Windows.Forms.Button()
        Me.Magz = New System.Windows.Forms.Label()
        Me.ListComMoteur = New System.Windows.Forms.ListBox()
        Me.TextBox_R_Moteur = New System.Windows.Forms.TextBox()
        Me.TextBox_Codeur = New System.Windows.Forms.TextBox()
        Me.ButtonCodeur = New System.Windows.Forms.Button()
        Me.M_Moteur = New System.Windows.Forms.Button()
        Me.Listµpas = New System.Windows.Forms.ListBox()
        Me.TextBoxSMoteur = New System.Windows.Forms.TextBox()
        Me.Button_S_Moteur = New System.Windows.Forms.Button()
        Me.TextBox_Reponse_m = New System.Windows.Forms.TextBox()
        Me.TextBox_reponse_s = New System.Windows.Forms.TextBox()
        Me.Button_Z_codeur = New System.Windows.Forms.Button()
        Me.StartMesure = New System.Windows.Forms.Button()
        Me.MagX1 = New System.Windows.Forms.Label()
        Me.TextBoxDebug = New System.Windows.Forms.TextBox()
        Me.Label_ID = New System.Windows.Forms.Label()
        Me.Label_Arduino_ID = New System.Windows.Forms.Label()
        Me.TextBox_Start_s = New System.Windows.Forms.TextBox()
        Me.TextBox_start_angle = New System.Windows.Forms.TextBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.ListBox_start_µpas = New System.Windows.Forms.ListBox()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.K_common = New System.Windows.Forms.Button()
        Me.TextBox_K_common_W = New System.Windows.Forms.TextBox()
        Me.K_common_w = New System.Windows.Forms.Button()
        Me.TextBox_Angle_2_offset_W = New System.Windows.Forms.TextBox()
        Me.Angle_2_offset_W = New System.Windows.Forms.Button()
        Me.Angle_2_offset = New System.Windows.Forms.Button()
        Me.TextBox_x_0_init_W = New System.Windows.Forms.TextBox()
        Me.x_0_init_W = New System.Windows.Forms.Button()
        Me.x_0_init = New System.Windows.Forms.Button()
        Me.TextBox_x_0_offset_W = New System.Windows.Forms.TextBox()
        Me.x_0_offset_W = New System.Windows.Forms.Button()
        Me.x_0_offset = New System.Windows.Forms.Button()
        Me.TextBox_Ka_BxC3_W = New System.Windows.Forms.TextBox()
        Me.Ka_BxC3_W = New System.Windows.Forms.Button()
        Me.Ka_BxC3 = New System.Windows.Forms.Button()
        Me.TextBox_Ka_BxC4_W = New System.Windows.Forms.TextBox()
        Me.Ka_BxC4_W = New System.Windows.Forms.Button()
        Me.Ka_BxC4 = New System.Windows.Forms.Button()
        Me.TextBox_Ka_ByC3_W = New System.Windows.Forms.TextBox()
        Me.Ka_ByC3_W = New System.Windows.Forms.Button()
        Me.Ka_ByC3 = New System.Windows.Forms.Button()
        Me.TextBox_Ka_BxC8_W = New System.Windows.Forms.TextBox()
        Me.Ka_BxC8_W = New System.Windows.Forms.Button()
        Me.Ka_BxC8 = New System.Windows.Forms.Button()
        Me.TextBox_Ka_BzC3_W = New System.Windows.Forms.TextBox()
        Me.Ka_BzC3_W = New System.Windows.Forms.Button()
        Me.Ka_BzC3 = New System.Windows.Forms.Button()
        Me.TextBox_Ka_BxC6_W = New System.Windows.Forms.TextBox()
        Me.Ka_BxC6_W = New System.Windows.Forms.Button()
        Me.Ka_BxC6 = New System.Windows.Forms.Button()
        Me.TextBox_nb_tours = New System.Windows.Forms.TextBox()
        Me.TextBox_deplacement = New System.Windows.Forms.TextBox()
        Me.Bat = New System.Windows.Forms.Button()
        Me.TextBat = New System.Windows.Forms.TextBox()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'SerialPort1
        '
        Me.SerialPort1.BaudRate = 460800
        Me.SerialPort1.Handshake = System.IO.Ports.Handshake.RequestToSend
        Me.SerialPort1.PortName = "COM10"
        Me.SerialPort1.ReadTimeout = 1000
        Me.SerialPort1.ReceivedBytesThreshold = 1000
        Me.SerialPort1.WriteBufferSize = 4096
        Me.SerialPort1.WriteTimeout = 1
        '
        'PictureBox1
        '
        Me.PictureBox1.Location = New System.Drawing.Point(0, 0)
        Me.PictureBox1.Name = "PictureBox1"
        Me.PictureBox1.Size = New System.Drawing.Size(161, 26)
        Me.PictureBox1.TabIndex = 18
        Me.PictureBox1.TabStop = False
        '
        'ListBox3
        '
        Me.ListBox3.BackColor = System.Drawing.Color.LawnGreen
        Me.ListBox3.ForeColor = System.Drawing.Color.Green
        Me.ListBox3.FormattingEnabled = True
        Me.ListBox3.ItemHeight = 24
        Me.ListBox3.Location = New System.Drawing.Point(12, 71)
        Me.ListBox3.Name = "ListBox3"
        Me.ListBox3.Size = New System.Drawing.Size(114, 100)
        Me.ListBox3.TabIndex = 76
        '
        'SerialPort2
        '
        Me.SerialPort2.BaudRate = 38400
        Me.SerialPort2.DtrEnable = True
        Me.SerialPort2.PortName = "COM10"
        Me.SerialPort2.ReadTimeout = 10
        Me.SerialPort2.ReceivedBytesThreshold = 10
        Me.SerialPort2.RtsEnable = True
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.BackColor = System.Drawing.SystemColors.ControlLightLight
        Me.Label2.Location = New System.Drawing.Point(418, 2)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(83, 24)
        Me.Label2.TabIndex = 80
        Me.Label2.Text = "V1.00.06"
        '
        'R_Moteur
        '
        Me.R_Moteur.BackColor = System.Drawing.Color.LawnGreen
        Me.R_Moteur.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.R_Moteur.ForeColor = System.Drawing.Color.Black
        Me.R_Moteur.Location = New System.Drawing.Point(297, 207)
        Me.R_Moteur.Name = "R_Moteur"
        Me.R_Moteur.Size = New System.Drawing.Size(101, 27)
        Me.R_Moteur.TabIndex = 123
        Me.R_Moteur.Text = "R moteur"
        Me.R_Moteur.UseVisualStyleBackColor = False
        '
        'Angle2
        '
        Me.Angle2.Location = New System.Drawing.Point(104, 244)
        Me.Angle2.Name = "Angle2"
        Me.Angle2.Size = New System.Drawing.Size(100, 24)
        Me.Angle2.TabIndex = 134
        '
        'Angle1
        '
        Me.Angle1.Location = New System.Drawing.Point(104, 211)
        Me.Angle1.Name = "Angle1"
        Me.Angle1.Size = New System.Drawing.Size(100, 24)
        Me.Angle1.TabIndex = 135
        '
        'Magx
        '
        Me.Magx.Location = New System.Drawing.Point(295, 429)
        Me.Magx.Name = "Magx"
        Me.Magx.Size = New System.Drawing.Size(100, 24)
        Me.Magx.TabIndex = 136
        '
        'Magy
        '
        Me.Magy.Location = New System.Drawing.Point(123, 314)
        Me.Magy.Name = "Magy"
        Me.Magy.Size = New System.Drawing.Size(81, 24)
        Me.Magy.TabIndex = 142
        '
        'Timer4
        '
        Me.Timer4.Interval = 1000
        '
        'ButtonAngle1
        '
        Me.ButtonAngle1.BackColor = System.Drawing.Color.LawnGreen
        Me.ButtonAngle1.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ButtonAngle1.ForeColor = System.Drawing.Color.Black
        Me.ButtonAngle1.Location = New System.Drawing.Point(12, 208)
        Me.ButtonAngle1.Name = "ButtonAngle1"
        Me.ButtonAngle1.Size = New System.Drawing.Size(86, 27)
        Me.ButtonAngle1.TabIndex = 149
        Me.ButtonAngle1.Text = "Angle1"
        Me.ButtonAngle1.UseVisualStyleBackColor = False
        '
        'ButtonAbgle2
        '
        Me.ButtonAbgle2.BackColor = System.Drawing.Color.LawnGreen
        Me.ButtonAbgle2.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ButtonAbgle2.ForeColor = System.Drawing.Color.Black
        Me.ButtonAbgle2.Location = New System.Drawing.Point(12, 241)
        Me.ButtonAbgle2.Name = "ButtonAbgle2"
        Me.ButtonAbgle2.Size = New System.Drawing.Size(86, 27)
        Me.ButtonAbgle2.TabIndex = 150
        Me.ButtonAbgle2.Text = "Angle2"
        Me.ButtonAbgle2.UseVisualStyleBackColor = False
        '
        'Mag
        '
        Me.Mag.BackColor = System.Drawing.Color.LawnGreen
        Me.Mag.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Mag.ForeColor = System.Drawing.Color.Black
        Me.Mag.Location = New System.Drawing.Point(12, 274)
        Me.Mag.Name = "Mag"
        Me.Mag.Size = New System.Drawing.Size(86, 107)
        Me.Mag.TabIndex = 151
        Me.Mag.Text = "Magneto"
        Me.Mag.UseVisualStyleBackColor = False
        '
        'Magz
        '
        Me.Magz.Location = New System.Drawing.Point(127, 354)
        Me.Magz.Name = "Magz"
        Me.Magz.Size = New System.Drawing.Size(77, 24)
        Me.Magz.TabIndex = 152
        '
        'ListComMoteur
        '
        Me.ListComMoteur.BackColor = System.Drawing.Color.LawnGreen
        Me.ListComMoteur.ForeColor = System.Drawing.Color.Green
        Me.ListComMoteur.FormattingEnabled = True
        Me.ListComMoteur.ItemHeight = 24
        Me.ListComMoteur.Location = New System.Drawing.Point(389, 70)
        Me.ListComMoteur.Name = "ListComMoteur"
        Me.ListComMoteur.Size = New System.Drawing.Size(111, 100)
        Me.ListComMoteur.TabIndex = 153
        '
        'TextBox_R_Moteur
        '
        Me.TextBox_R_Moteur.Location = New System.Drawing.Point(401, 207)
        Me.TextBox_R_Moteur.Name = "TextBox_R_Moteur"
        Me.TextBox_R_Moteur.Size = New System.Drawing.Size(100, 29)
        Me.TextBox_R_Moteur.TabIndex = 154
        '
        'TextBox_Codeur
        '
        Me.TextBox_Codeur.Location = New System.Drawing.Point(398, 275)
        Me.TextBox_Codeur.Name = "TextBox_Codeur"
        Me.TextBox_Codeur.Size = New System.Drawing.Size(100, 29)
        Me.TextBox_Codeur.TabIndex = 155
        '
        'ButtonCodeur
        '
        Me.ButtonCodeur.BackColor = System.Drawing.Color.LawnGreen
        Me.ButtonCodeur.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ButtonCodeur.ForeColor = System.Drawing.Color.Black
        Me.ButtonCodeur.Location = New System.Drawing.Point(297, 275)
        Me.ButtonCodeur.Name = "ButtonCodeur"
        Me.ButtonCodeur.Size = New System.Drawing.Size(101, 27)
        Me.ButtonCodeur.TabIndex = 156
        Me.ButtonCodeur.Text = "C  moteur"
        Me.ButtonCodeur.UseVisualStyleBackColor = False
        '
        'M_Moteur
        '
        Me.M_Moteur.BackColor = System.Drawing.Color.LawnGreen
        Me.M_Moteur.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.M_Moteur.ForeColor = System.Drawing.Color.Black
        Me.M_Moteur.Location = New System.Drawing.Point(297, 314)
        Me.M_Moteur.Name = "M_Moteur"
        Me.M_Moteur.Size = New System.Drawing.Size(101, 27)
        Me.M_Moteur.TabIndex = 157
        Me.M_Moteur.Text = "M_Moteur"
        Me.M_Moteur.UseVisualStyleBackColor = False
        '
        'Listµpas
        '
        Me.Listµpas.FormattingEnabled = True
        Me.Listµpas.ItemHeight = 24
        Me.Listµpas.Location = New System.Drawing.Point(401, 317)
        Me.Listµpas.Name = "Listµpas"
        Me.Listµpas.Size = New System.Drawing.Size(97, 76)
        Me.Listµpas.TabIndex = 158
        '
        'TextBoxSMoteur
        '
        Me.TextBoxSMoteur.Location = New System.Drawing.Point(398, 399)
        Me.TextBoxSMoteur.Name = "TextBoxSMoteur"
        Me.TextBoxSMoteur.Size = New System.Drawing.Size(100, 29)
        Me.TextBoxSMoteur.TabIndex = 160
        '
        'Button_S_Moteur
        '
        Me.Button_S_Moteur.BackColor = System.Drawing.Color.LawnGreen
        Me.Button_S_Moteur.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button_S_Moteur.ForeColor = System.Drawing.Color.Black
        Me.Button_S_Moteur.Location = New System.Drawing.Point(294, 399)
        Me.Button_S_Moteur.Name = "Button_S_Moteur"
        Me.Button_S_Moteur.Size = New System.Drawing.Size(101, 27)
        Me.Button_S_Moteur.TabIndex = 159
        Me.Button_S_Moteur.Text = "S moteur"
        Me.Button_S_Moteur.UseVisualStyleBackColor = False
        '
        'TextBox_Reponse_m
        '
        Me.TextBox_Reponse_m.Location = New System.Drawing.Point(295, 347)
        Me.TextBox_Reponse_m.Name = "TextBox_Reponse_m"
        Me.TextBox_Reponse_m.Size = New System.Drawing.Size(100, 29)
        Me.TextBox_Reponse_m.TabIndex = 161
        '
        'TextBox_reponse_s
        '
        Me.TextBox_reponse_s.Location = New System.Drawing.Point(295, 429)
        Me.TextBox_reponse_s.Name = "TextBox_reponse_s"
        Me.TextBox_reponse_s.Size = New System.Drawing.Size(100, 29)
        Me.TextBox_reponse_s.TabIndex = 162
        '
        'Button_Z_codeur
        '
        Me.Button_Z_codeur.BackColor = System.Drawing.Color.LawnGreen
        Me.Button_Z_codeur.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button_Z_codeur.ForeColor = System.Drawing.Color.Black
        Me.Button_Z_codeur.Location = New System.Drawing.Point(297, 240)
        Me.Button_Z_codeur.Name = "Button_Z_codeur"
        Me.Button_Z_codeur.Size = New System.Drawing.Size(101, 27)
        Me.Button_Z_codeur.TabIndex = 163
        Me.Button_Z_codeur.Text = "Z moteur"
        Me.Button_Z_codeur.UseVisualStyleBackColor = False
        '
        'StartMesure
        '
        Me.StartMesure.BackColor = System.Drawing.Color.LawnGreen
        Me.StartMesure.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.StartMesure.ForeColor = System.Drawing.Color.Black
        Me.StartMesure.Location = New System.Drawing.Point(13, 75)
        Me.StartMesure.Name = "StartMesure"
        Me.StartMesure.Size = New System.Drawing.Size(101, 27)
        Me.StartMesure.TabIndex = 164
        Me.StartMesure.Text = "Start Mesures"
        Me.StartMesure.UseVisualStyleBackColor = False
        '
        'MagX1
        '
        Me.MagX1.Location = New System.Drawing.Point(127, 279)
        Me.MagX1.Name = "MagX1"
        Me.MagX1.Size = New System.Drawing.Size(77, 24)
        Me.MagX1.TabIndex = 165
        '
        'TextBoxDebug
        '
        Me.TextBoxDebug.Font = New System.Drawing.Font("Microsoft Sans Serif", 10.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TextBoxDebug.Location = New System.Drawing.Point(13, 198)
        Me.TextBoxDebug.Multiline = True
        Me.TextBoxDebug.Name = "TextBoxDebug"
        Me.TextBoxDebug.Size = New System.Drawing.Size(488, 540)
        Me.TextBoxDebug.TabIndex = 166
        '
        'Label_ID
        '
        Me.Label_ID.Location = New System.Drawing.Point(12, 44)
        Me.Label_ID.Name = "Label_ID"
        Me.Label_ID.Size = New System.Drawing.Size(197, 24)
        Me.Label_ID.TabIndex = 168
        '
        'Label_Arduino_ID
        '
        Me.Label_Arduino_ID.Location = New System.Drawing.Point(303, 43)
        Me.Label_Arduino_ID.Name = "Label_Arduino_ID"
        Me.Label_Arduino_ID.Size = New System.Drawing.Size(197, 24)
        Me.Label_Arduino_ID.TabIndex = 169
        '
        'TextBox_Start_s
        '
        Me.TextBox_Start_s.Location = New System.Drawing.Point(13, 143)
        Me.TextBox_Start_s.Name = "TextBox_Start_s"
        Me.TextBox_Start_s.Size = New System.Drawing.Size(78, 29)
        Me.TextBox_Start_s.TabIndex = 170
        '
        'TextBox_start_angle
        '
        Me.TextBox_start_angle.Location = New System.Drawing.Point(13, 108)
        Me.TextBox_start_angle.Name = "TextBox_start_angle"
        Me.TextBox_start_angle.Size = New System.Drawing.Size(61, 29)
        Me.TextBox_start_angle.TabIndex = 172
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.ForeColor = System.Drawing.Color.Yellow
        Me.Label1.Location = New System.Drawing.Point(80, 111)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(71, 24)
        Me.Label1.TabIndex = 173
        Me.Label1.Text = "Degrés"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.ForeColor = System.Drawing.Color.Yellow
        Me.Label3.Location = New System.Drawing.Point(97, 146)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(64, 24)
        Me.Label3.TabIndex = 174
        Me.Label3.Text = "Tr/min"
        '
        'ListBox_start_µpas
        '
        Me.ListBox_start_µpas.FormattingEnabled = True
        Me.ListBox_start_µpas.ItemHeight = 24
        Me.ListBox_start_µpas.Location = New System.Drawing.Point(167, 108)
        Me.ListBox_start_µpas.Name = "ListBox_start_µpas"
        Me.ListBox_start_µpas.Size = New System.Drawing.Size(120, 76)
        Me.ListBox_start_µpas.TabIndex = 175
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.ForeColor = System.Drawing.Color.Yellow
        Me.Label4.Location = New System.Drawing.Point(293, 113)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(49, 24)
        Me.Label4.TabIndex = 176
        Me.Label4.Text = "µpas"
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.ForeColor = System.Drawing.Color.Yellow
        Me.Label5.Location = New System.Drawing.Point(104, 279)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(24, 24)
        Me.Label5.TabIndex = 177
        Me.Label5.Text = "X"
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.ForeColor = System.Drawing.Color.Yellow
        Me.Label6.Location = New System.Drawing.Point(104, 314)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(22, 24)
        Me.Label6.TabIndex = 178
        Me.Label6.Text = "Y"
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.ForeColor = System.Drawing.Color.Yellow
        Me.Label7.Location = New System.Drawing.Point(104, 353)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(22, 24)
        Me.Label7.TabIndex = 179
        Me.Label7.Text = "Z"
        '
        'Timer1
        '
        Me.Timer1.Interval = 1000
        '
        'K_common
        '
        Me.K_common.BackColor = System.Drawing.Color.LawnGreen
        Me.K_common.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.K_common.ForeColor = System.Drawing.Color.Black
        Me.K_common.Location = New System.Drawing.Point(1228, 72)
        Me.K_common.Name = "K_common"
        Me.K_common.Size = New System.Drawing.Size(161, 27)
        Me.K_common.TabIndex = 180
        Me.K_common.Text = "K_common"
        Me.K_common.UseVisualStyleBackColor = False
        '
        'TextBox_K_common_W
        '
        Me.TextBox_K_common_W.Location = New System.Drawing.Point(702, 72)
        Me.TextBox_K_common_W.Name = "TextBox_K_common_W"
        Me.TextBox_K_common_W.Size = New System.Drawing.Size(115, 29)
        Me.TextBox_K_common_W.TabIndex = 183
        '
        'K_common_w
        '
        Me.K_common_w.BackColor = System.Drawing.Color.LawnGreen
        Me.K_common_w.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.K_common_w.ForeColor = System.Drawing.Color.Black
        Me.K_common_w.Location = New System.Drawing.Point(537, 72)
        Me.K_common_w.Name = "K_common_w"
        Me.K_common_w.Size = New System.Drawing.Size(159, 27)
        Me.K_common_w.TabIndex = 182
        Me.K_common_w.Text = "K_common_W"
        Me.K_common_w.UseVisualStyleBackColor = False
        '
        'TextBox_Angle_2_offset_W
        '
        Me.TextBox_Angle_2_offset_W.Location = New System.Drawing.Point(702, 106)
        Me.TextBox_Angle_2_offset_W.Name = "TextBox_Angle_2_offset_W"
        Me.TextBox_Angle_2_offset_W.Size = New System.Drawing.Size(115, 29)
        Me.TextBox_Angle_2_offset_W.TabIndex = 187
        '
        'Angle_2_offset_W
        '
        Me.Angle_2_offset_W.BackColor = System.Drawing.Color.LawnGreen
        Me.Angle_2_offset_W.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Angle_2_offset_W.ForeColor = System.Drawing.Color.Black
        Me.Angle_2_offset_W.Location = New System.Drawing.Point(537, 105)
        Me.Angle_2_offset_W.Name = "Angle_2_offset_W"
        Me.Angle_2_offset_W.Size = New System.Drawing.Size(159, 27)
        Me.Angle_2_offset_W.TabIndex = 186
        Me.Angle_2_offset_W.Text = "Angle_2_offset_W"
        Me.Angle_2_offset_W.UseVisualStyleBackColor = False
        '
        'Angle_2_offset
        '
        Me.Angle_2_offset.BackColor = System.Drawing.Color.LawnGreen
        Me.Angle_2_offset.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Angle_2_offset.ForeColor = System.Drawing.Color.Black
        Me.Angle_2_offset.Location = New System.Drawing.Point(1228, 107)
        Me.Angle_2_offset.Name = "Angle_2_offset"
        Me.Angle_2_offset.Size = New System.Drawing.Size(161, 27)
        Me.Angle_2_offset.TabIndex = 184
        Me.Angle_2_offset.Text = "Angle_2_offset"
        Me.Angle_2_offset.UseVisualStyleBackColor = False
        '
        'TextBox_x_0_init_W
        '
        Me.TextBox_x_0_init_W.Location = New System.Drawing.Point(702, 141)
        Me.TextBox_x_0_init_W.Name = "TextBox_x_0_init_W"
        Me.TextBox_x_0_init_W.Size = New System.Drawing.Size(115, 29)
        Me.TextBox_x_0_init_W.TabIndex = 191
        '
        'x_0_init_W
        '
        Me.x_0_init_W.BackColor = System.Drawing.Color.LawnGreen
        Me.x_0_init_W.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.x_0_init_W.ForeColor = System.Drawing.Color.Black
        Me.x_0_init_W.Location = New System.Drawing.Point(537, 142)
        Me.x_0_init_W.Name = "x_0_init_W"
        Me.x_0_init_W.Size = New System.Drawing.Size(159, 27)
        Me.x_0_init_W.TabIndex = 190
        Me.x_0_init_W.Text = "x_0_init_W"
        Me.x_0_init_W.UseVisualStyleBackColor = False
        '
        'x_0_init
        '
        Me.x_0_init.BackColor = System.Drawing.Color.LawnGreen
        Me.x_0_init.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.x_0_init.ForeColor = System.Drawing.Color.Black
        Me.x_0_init.Location = New System.Drawing.Point(1228, 142)
        Me.x_0_init.Name = "x_0_init"
        Me.x_0_init.Size = New System.Drawing.Size(161, 27)
        Me.x_0_init.TabIndex = 188
        Me.x_0_init.Text = "x_0_init"
        Me.x_0_init.UseVisualStyleBackColor = False
        '
        'TextBox_x_0_offset_W
        '
        Me.TextBox_x_0_offset_W.Location = New System.Drawing.Point(702, 176)
        Me.TextBox_x_0_offset_W.Name = "TextBox_x_0_offset_W"
        Me.TextBox_x_0_offset_W.Size = New System.Drawing.Size(115, 29)
        Me.TextBox_x_0_offset_W.TabIndex = 195
        '
        'x_0_offset_W
        '
        Me.x_0_offset_W.BackColor = System.Drawing.Color.LawnGreen
        Me.x_0_offset_W.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.x_0_offset_W.ForeColor = System.Drawing.Color.Black
        Me.x_0_offset_W.Location = New System.Drawing.Point(537, 177)
        Me.x_0_offset_W.Name = "x_0_offset_W"
        Me.x_0_offset_W.Size = New System.Drawing.Size(159, 27)
        Me.x_0_offset_W.TabIndex = 194
        Me.x_0_offset_W.Text = "x_0_offset_W"
        Me.x_0_offset_W.UseVisualStyleBackColor = False
        '
        'x_0_offset
        '
        Me.x_0_offset.BackColor = System.Drawing.Color.LawnGreen
        Me.x_0_offset.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.x_0_offset.ForeColor = System.Drawing.Color.Black
        Me.x_0_offset.Location = New System.Drawing.Point(1228, 177)
        Me.x_0_offset.Name = "x_0_offset"
        Me.x_0_offset.Size = New System.Drawing.Size(161, 27)
        Me.x_0_offset.TabIndex = 192
        Me.x_0_offset.Text = "x_0_offset"
        Me.x_0_offset.UseVisualStyleBackColor = False
        '
        'TextBox_Ka_BxC3_W
        '
        Me.TextBox_Ka_BxC3_W.Location = New System.Drawing.Point(702, 210)
        Me.TextBox_Ka_BxC3_W.Name = "TextBox_Ka_BxC3_W"
        Me.TextBox_Ka_BxC3_W.Size = New System.Drawing.Size(115, 29)
        Me.TextBox_Ka_BxC3_W.TabIndex = 199
        '
        'Ka_BxC3_W
        '
        Me.Ka_BxC3_W.BackColor = System.Drawing.Color.LawnGreen
        Me.Ka_BxC3_W.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Ka_BxC3_W.ForeColor = System.Drawing.Color.Black
        Me.Ka_BxC3_W.Location = New System.Drawing.Point(537, 210)
        Me.Ka_BxC3_W.Name = "Ka_BxC3_W"
        Me.Ka_BxC3_W.Size = New System.Drawing.Size(159, 27)
        Me.Ka_BxC3_W.TabIndex = 198
        Me.Ka_BxC3_W.Text = "Ka_BxC3_W"
        Me.Ka_BxC3_W.UseVisualStyleBackColor = False
        '
        'Ka_BxC3
        '
        Me.Ka_BxC3.BackColor = System.Drawing.Color.LawnGreen
        Me.Ka_BxC3.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Ka_BxC3.ForeColor = System.Drawing.Color.Black
        Me.Ka_BxC3.Location = New System.Drawing.Point(1228, 210)
        Me.Ka_BxC3.Name = "Ka_BxC3"
        Me.Ka_BxC3.Size = New System.Drawing.Size(161, 27)
        Me.Ka_BxC3.TabIndex = 196
        Me.Ka_BxC3.Text = "Ka_BxC3"
        Me.Ka_BxC3.UseVisualStyleBackColor = False
        '
        'TextBox_Ka_BxC4_W
        '
        Me.TextBox_Ka_BxC4_W.Location = New System.Drawing.Point(702, 245)
        Me.TextBox_Ka_BxC4_W.Name = "TextBox_Ka_BxC4_W"
        Me.TextBox_Ka_BxC4_W.Size = New System.Drawing.Size(115, 29)
        Me.TextBox_Ka_BxC4_W.TabIndex = 203
        '
        'Ka_BxC4_W
        '
        Me.Ka_BxC4_W.BackColor = System.Drawing.Color.LawnGreen
        Me.Ka_BxC4_W.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Ka_BxC4_W.ForeColor = System.Drawing.Color.Black
        Me.Ka_BxC4_W.Location = New System.Drawing.Point(537, 242)
        Me.Ka_BxC4_W.Name = "Ka_BxC4_W"
        Me.Ka_BxC4_W.Size = New System.Drawing.Size(159, 27)
        Me.Ka_BxC4_W.TabIndex = 202
        Me.Ka_BxC4_W.Text = "Kb_BxC3_W"
        Me.Ka_BxC4_W.UseVisualStyleBackColor = False
        '
        'Ka_BxC4
        '
        Me.Ka_BxC4.BackColor = System.Drawing.Color.LawnGreen
        Me.Ka_BxC4.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Ka_BxC4.ForeColor = System.Drawing.Color.Black
        Me.Ka_BxC4.Location = New System.Drawing.Point(1228, 245)
        Me.Ka_BxC4.Name = "Ka_BxC4"
        Me.Ka_BxC4.Size = New System.Drawing.Size(161, 27)
        Me.Ka_BxC4.TabIndex = 200
        Me.Ka_BxC4.Text = "Kb_BxC3"
        Me.Ka_BxC4.UseVisualStyleBackColor = False
        '
        'TextBox_Ka_ByC3_W
        '
        Me.TextBox_Ka_ByC3_W.Location = New System.Drawing.Point(702, 277)
        Me.TextBox_Ka_ByC3_W.Name = "TextBox_Ka_ByC3_W"
        Me.TextBox_Ka_ByC3_W.Size = New System.Drawing.Size(115, 29)
        Me.TextBox_Ka_ByC3_W.TabIndex = 207
        '
        'Ka_ByC3_W
        '
        Me.Ka_ByC3_W.BackColor = System.Drawing.Color.LawnGreen
        Me.Ka_ByC3_W.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Ka_ByC3_W.ForeColor = System.Drawing.Color.Black
        Me.Ka_ByC3_W.Location = New System.Drawing.Point(537, 276)
        Me.Ka_ByC3_W.Name = "Ka_ByC3_W"
        Me.Ka_ByC3_W.Size = New System.Drawing.Size(159, 27)
        Me.Ka_ByC3_W.TabIndex = 206
        Me.Ka_ByC3_W.Text = "Ka_ByC3_W"
        Me.Ka_ByC3_W.UseVisualStyleBackColor = False
        '
        'Ka_ByC3
        '
        Me.Ka_ByC3.BackColor = System.Drawing.Color.LawnGreen
        Me.Ka_ByC3.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Ka_ByC3.ForeColor = System.Drawing.Color.Black
        Me.Ka_ByC3.Location = New System.Drawing.Point(1228, 276)
        Me.Ka_ByC3.Name = "Ka_ByC3"
        Me.Ka_ByC3.Size = New System.Drawing.Size(161, 27)
        Me.Ka_ByC3.TabIndex = 204
        Me.Ka_ByC3.Text = "Ka_ByC3"
        Me.Ka_ByC3.UseVisualStyleBackColor = False
        '
        'TextBox_Ka_BxC8_W
        '
        Me.TextBox_Ka_BxC8_W.Location = New System.Drawing.Point(702, 381)
        Me.TextBox_Ka_BxC8_W.Name = "TextBox_Ka_BxC8_W"
        Me.TextBox_Ka_BxC8_W.Size = New System.Drawing.Size(115, 29)
        Me.TextBox_Ka_BxC8_W.TabIndex = 219
        '
        'Ka_BxC8_W
        '
        Me.Ka_BxC8_W.BackColor = System.Drawing.Color.LawnGreen
        Me.Ka_BxC8_W.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Ka_BxC8_W.ForeColor = System.Drawing.Color.Black
        Me.Ka_BxC8_W.Location = New System.Drawing.Point(537, 381)
        Me.Ka_BxC8_W.Name = "Ka_BxC8_W"
        Me.Ka_BxC8_W.Size = New System.Drawing.Size(159, 27)
        Me.Ka_BxC8_W.TabIndex = 218
        Me.Ka_BxC8_W.Text = "Kb_BzC3_W"
        Me.Ka_BxC8_W.UseVisualStyleBackColor = False
        '
        'Ka_BxC8
        '
        Me.Ka_BxC8.BackColor = System.Drawing.Color.LawnGreen
        Me.Ka_BxC8.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Ka_BxC8.ForeColor = System.Drawing.Color.Black
        Me.Ka_BxC8.Location = New System.Drawing.Point(1228, 381)
        Me.Ka_BxC8.Name = "Ka_BxC8"
        Me.Ka_BxC8.Size = New System.Drawing.Size(161, 27)
        Me.Ka_BxC8.TabIndex = 216
        Me.Ka_BxC8.Text = "Kb_BzC3"
        Me.Ka_BxC8.UseVisualStyleBackColor = False
        '
        'TextBox_Ka_BzC3_W
        '
        Me.TextBox_Ka_BzC3_W.Location = New System.Drawing.Point(702, 346)
        Me.TextBox_Ka_BzC3_W.Name = "TextBox_Ka_BzC3_W"
        Me.TextBox_Ka_BzC3_W.Size = New System.Drawing.Size(115, 29)
        Me.TextBox_Ka_BzC3_W.TabIndex = 215
        '
        'Ka_BzC3_W
        '
        Me.Ka_BzC3_W.BackColor = System.Drawing.Color.LawnGreen
        Me.Ka_BzC3_W.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Ka_BzC3_W.ForeColor = System.Drawing.Color.Black
        Me.Ka_BzC3_W.Location = New System.Drawing.Point(537, 346)
        Me.Ka_BzC3_W.Name = "Ka_BzC3_W"
        Me.Ka_BzC3_W.Size = New System.Drawing.Size(159, 27)
        Me.Ka_BzC3_W.TabIndex = 214
        Me.Ka_BzC3_W.Text = "Ka_BzC3_W"
        Me.Ka_BzC3_W.UseVisualStyleBackColor = False
        '
        'Ka_BzC3
        '
        Me.Ka_BzC3.BackColor = System.Drawing.Color.LawnGreen
        Me.Ka_BzC3.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Ka_BzC3.ForeColor = System.Drawing.Color.Black
        Me.Ka_BzC3.Location = New System.Drawing.Point(1228, 346)
        Me.Ka_BzC3.Name = "Ka_BzC3"
        Me.Ka_BzC3.Size = New System.Drawing.Size(161, 27)
        Me.Ka_BzC3.TabIndex = 212
        Me.Ka_BzC3.Text = "Ka_BzC3"
        Me.Ka_BzC3.UseVisualStyleBackColor = False
        '
        'TextBox_Ka_BxC6_W
        '
        Me.TextBox_Ka_BxC6_W.Location = New System.Drawing.Point(702, 311)
        Me.TextBox_Ka_BxC6_W.Name = "TextBox_Ka_BxC6_W"
        Me.TextBox_Ka_BxC6_W.Size = New System.Drawing.Size(115, 29)
        Me.TextBox_Ka_BxC6_W.TabIndex = 211
        '
        'Ka_BxC6_W
        '
        Me.Ka_BxC6_W.BackColor = System.Drawing.Color.LawnGreen
        Me.Ka_BxC6_W.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Ka_BxC6_W.ForeColor = System.Drawing.Color.Black
        Me.Ka_BxC6_W.Location = New System.Drawing.Point(537, 311)
        Me.Ka_BxC6_W.Name = "Ka_BxC6_W"
        Me.Ka_BxC6_W.Size = New System.Drawing.Size(159, 27)
        Me.Ka_BxC6_W.TabIndex = 210
        Me.Ka_BxC6_W.Text = "Kb_ByC3_W"
        Me.Ka_BxC6_W.UseVisualStyleBackColor = False
        '
        'Ka_BxC6
        '
        Me.Ka_BxC6.BackColor = System.Drawing.Color.LawnGreen
        Me.Ka_BxC6.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Ka_BxC6.ForeColor = System.Drawing.Color.Black
        Me.Ka_BxC6.Location = New System.Drawing.Point(1228, 309)
        Me.Ka_BxC6.Name = "Ka_BxC6"
        Me.Ka_BxC6.Size = New System.Drawing.Size(161, 27)
        Me.Ka_BxC6.TabIndex = 208
        Me.Ka_BxC6.Text = "Kb_ByC3"
        Me.Ka_BxC6.UseVisualStyleBackColor = False
        '
        'TextBox_nb_tours
        '
        Me.TextBox_nb_tours.Font = New System.Drawing.Font("MS Gothic", 100.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TextBox_nb_tours.Location = New System.Drawing.Point(520, 429)
        Me.TextBox_nb_tours.Name = "TextBox_nb_tours"
        Me.TextBox_nb_tours.Size = New System.Drawing.Size(548, 141)
        Me.TextBox_nb_tours.TabIndex = 220
        '
        'TextBox_deplacement
        '
        Me.TextBox_deplacement.Font = New System.Drawing.Font("MS Gothic", 100.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TextBox_deplacement.Location = New System.Drawing.Point(520, 585)
        Me.TextBox_deplacement.Name = "TextBox_deplacement"
        Me.TextBox_deplacement.Size = New System.Drawing.Size(548, 141)
        Me.TextBox_deplacement.TabIndex = 221
        '
        'Bat
        '
        Me.Bat.BackColor = System.Drawing.Color.LawnGreen
        Me.Bat.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Bat.ForeColor = System.Drawing.Color.Black
        Me.Bat.Location = New System.Drawing.Point(823, 74)
        Me.Bat.Name = "Bat"
        Me.Bat.Size = New System.Drawing.Size(95, 27)
        Me.Bat.TabIndex = 222
        Me.Bat.Text = "Bat"
        Me.Bat.UseVisualStyleBackColor = False
        '
        'TextBat
        '
        Me.TextBat.Location = New System.Drawing.Point(924, 71)
        Me.TextBat.Name = "TextBat"
        Me.TextBat.Size = New System.Drawing.Size(115, 29)
        Me.TextBat.TabIndex = 223
        '
        'BlueSoft
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(11.0!, 24.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.HotTrack
        Me.ClientSize = New System.Drawing.Size(1080, 750)
        Me.Controls.Add(Me.TextBat)
        Me.Controls.Add(Me.Bat)
        Me.Controls.Add(Me.TextBox_deplacement)
        Me.Controls.Add(Me.TextBox_nb_tours)
        Me.Controls.Add(Me.TextBox_Ka_BxC8_W)
        Me.Controls.Add(Me.Ka_BxC8_W)
        Me.Controls.Add(Me.Ka_BxC8)
        Me.Controls.Add(Me.TextBox_Ka_BzC3_W)
        Me.Controls.Add(Me.Ka_BzC3_W)
        Me.Controls.Add(Me.Ka_BzC3)
        Me.Controls.Add(Me.TextBox_Ka_BxC6_W)
        Me.Controls.Add(Me.Ka_BxC6_W)
        Me.Controls.Add(Me.Ka_BxC6)
        Me.Controls.Add(Me.TextBox_Ka_ByC3_W)
        Me.Controls.Add(Me.Ka_ByC3_W)
        Me.Controls.Add(Me.Ka_ByC3)
        Me.Controls.Add(Me.TextBox_Ka_BxC4_W)
        Me.Controls.Add(Me.Ka_BxC4_W)
        Me.Controls.Add(Me.Ka_BxC4)
        Me.Controls.Add(Me.TextBox_Ka_BxC3_W)
        Me.Controls.Add(Me.Ka_BxC3_W)
        Me.Controls.Add(Me.Ka_BxC3)
        Me.Controls.Add(Me.TextBox_x_0_offset_W)
        Me.Controls.Add(Me.x_0_offset_W)
        Me.Controls.Add(Me.x_0_offset)
        Me.Controls.Add(Me.TextBox_x_0_init_W)
        Me.Controls.Add(Me.x_0_init_W)
        Me.Controls.Add(Me.x_0_init)
        Me.Controls.Add(Me.TextBox_Angle_2_offset_W)
        Me.Controls.Add(Me.Angle_2_offset_W)
        Me.Controls.Add(Me.Angle_2_offset)
        Me.Controls.Add(Me.TextBox_K_common_W)
        Me.Controls.Add(Me.K_common_w)
        Me.Controls.Add(Me.K_common)
        Me.Controls.Add(Me.Label7)
        Me.Controls.Add(Me.Label6)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.ListBox_start_µpas)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.TextBox_start_angle)
        Me.Controls.Add(Me.TextBox_Start_s)
        Me.Controls.Add(Me.Label_Arduino_ID)
        Me.Controls.Add(Me.Label_ID)
        Me.Controls.Add(Me.TextBoxDebug)
        Me.Controls.Add(Me.MagX1)
        Me.Controls.Add(Me.StartMesure)
        Me.Controls.Add(Me.Button_Z_codeur)
        Me.Controls.Add(Me.TextBox_reponse_s)
        Me.Controls.Add(Me.TextBox_Reponse_m)
        Me.Controls.Add(Me.TextBoxSMoteur)
        Me.Controls.Add(Me.Button_S_Moteur)
        Me.Controls.Add(Me.Listµpas)
        Me.Controls.Add(Me.M_Moteur)
        Me.Controls.Add(Me.ButtonCodeur)
        Me.Controls.Add(Me.TextBox_Codeur)
        Me.Controls.Add(Me.TextBox_R_Moteur)
        Me.Controls.Add(Me.ListComMoteur)
        Me.Controls.Add(Me.Magz)
        Me.Controls.Add(Me.Mag)
        Me.Controls.Add(Me.ButtonAbgle2)
        Me.Controls.Add(Me.ButtonAngle1)
        Me.Controls.Add(Me.Magy)
        Me.Controls.Add(Me.Magx)
        Me.Controls.Add(Me.Angle1)
        Me.Controls.Add(Me.Angle2)
        Me.Controls.Add(Me.R_Moteur)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.ListBox3)
        Me.Controls.Add(Me.PictureBox1)
        Me.Cursor = System.Windows.Forms.Cursors.Default
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 14.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.Color.Black
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Margin = New System.Windows.Forms.Padding(5)
        Me.Name = "BlueSoft"
        Me.Text = "Compteur"
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents PictureBox1 As System.Windows.Forms.PictureBox
    Private WithEvents SerialPort1 As System.IO.Ports.SerialPort
    Friend WithEvents ListBox3 As System.Windows.Forms.ListBox
    Private WithEvents SerialPort2 As System.IO.Ports.SerialPort
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents R_Moteur As Button
    Friend WithEvents Angle2 As Label
    Friend WithEvents Angle1 As Label
    Friend WithEvents Magx As Label
    Friend WithEvents Magy As Label
    Friend WithEvents Timer4 As Timer
    Friend WithEvents ButtonAngle1 As Button
    Friend WithEvents ButtonAbgle2 As Button
    Friend WithEvents Mag As Button
    Friend WithEvents Magz As Label
    Friend WithEvents ListComMoteur As ListBox
    Friend WithEvents TextBox_R_Moteur As TextBox
    Friend WithEvents TextBox_Codeur As TextBox
    Friend WithEvents ButtonCodeur As Button
    Friend WithEvents M_Moteur As Button
    Friend WithEvents Listµpas As ListBox
    Friend WithEvents TextBoxSMoteur As TextBox
    Friend WithEvents Button_S_Moteur As Button
    Friend WithEvents TextBox_Reponse_m As TextBox
    Friend WithEvents TextBox_reponse_s As TextBox
    Friend WithEvents Button_Z_codeur As Button
    Friend WithEvents StartMesure As Button
    Friend WithEvents MagX1 As Label
    Friend WithEvents TextBoxDebug As TextBox
    Friend WithEvents Label_ID As Label
    Friend WithEvents Label_Arduino_ID As Label
    Friend WithEvents TextBox_Start_s As TextBox
    Friend WithEvents TextBox_start_angle As TextBox
    Friend WithEvents Label1 As Label
    Friend WithEvents Label3 As Label
    Friend WithEvents ListBox_start_µpas As ListBox
    Friend WithEvents Label4 As Label
    Friend WithEvents Label5 As Label
    Friend WithEvents Label6 As Label
    Friend WithEvents Label7 As Label
    Friend WithEvents Timer1 As Timer
    Friend WithEvents K_common As Button
    Friend WithEvents TextBox_K_common_W As TextBox
    Friend WithEvents K_common_w As Button
    Friend WithEvents TextBox_Angle_2_offset_W As TextBox
    Friend WithEvents Angle_2_offset_W As Button
    Friend WithEvents Angle_2_offset As Button
    Friend WithEvents TextBox_x_0_init_W As TextBox
    Friend WithEvents x_0_init_W As Button
    Friend WithEvents x_0_init As Button
    Friend WithEvents TextBox_x_0_offset_W As TextBox
    Friend WithEvents x_0_offset_W As Button
    Friend WithEvents x_0_offset As Button
    Friend WithEvents TextBox_Ka_BxC3_W As TextBox
    Friend WithEvents Ka_BxC3_W As Button
    Friend WithEvents Ka_BxC3 As Button
    Friend WithEvents TextBox_Ka_BxC4_W As TextBox
    Friend WithEvents Ka_BxC4_W As Button
    Friend WithEvents Ka_BxC4 As Button
    Friend WithEvents TextBox_Ka_ByC3_W As TextBox
    Friend WithEvents Ka_ByC3_W As Button
    Friend WithEvents Ka_ByC3 As Button
    Friend WithEvents TextBox_Ka_BxC8_W As TextBox
    Friend WithEvents Ka_BxC8_W As Button
    Friend WithEvents Ka_BxC8 As Button
    Friend WithEvents TextBox_Ka_BzC3_W As TextBox
    Friend WithEvents Ka_BzC3_W As Button
    Friend WithEvents Ka_BzC3 As Button
    Friend WithEvents TextBox_Ka_BxC6_W As TextBox
    Friend WithEvents Ka_BxC6_W As Button
    Friend WithEvents Ka_BxC6 As Button
    Friend WithEvents TextBox_nb_tours As TextBox
    Friend WithEvents TextBox_deplacement As TextBox
    Friend WithEvents Bat As Button
    Friend WithEvents TextBat As TextBox
End Class
