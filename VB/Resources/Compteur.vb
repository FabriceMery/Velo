Imports System.Windows.Forms.DataVisualization.Charting
Imports System.Math
Imports System.IO



Public Class BlueSoft
    Dim debug As String = ""
    Dim NameFile_log As String
    Dim Value(1000) As Char
    Dim Valuetest(10000) As Char
    Dim PintValuetest As Integer = 0
    Dim Value1(50) As Char
    Dim PextValue As Integer = 0
    Dim PintValue As Integer = 0
    Dim PextValueSav As Integer = 0
    Dim Value_moteur(10000) As Char
    Dim PextValue_moteur As Integer = 0
    Dim PintValue_moteur As Integer = 0
    Dim PORT1 As String = ""
    Dim PORT2 As String = ""
    Dim MessageCommande As String = ""
    Dim Message_protocol(500) As Char
    Dim Message(500) As Char

    Dim string_Aff(500) As String
    Dim string_cptTotal As String = ""
    Dim string_angle1 As String = ""
    Dim string_angle2 As String = ""
    Dim string_magx As String = ""
    Dim string_magy As String = ""
    Dim string_magz As String = ""
    Dim string_counbterId As String = ""
    Dim String_K_common As String = ""
    Dim String_Angle_2_offset As String = ""
    Dim String_x_0_init As String = ""
    Dim String_x_0_offset As String = ""
    Dim String_Ka_BxC3 As String = ""
    Dim String_Ka_BxC4 As String = ""
    Dim String_Ka_ByC3 As String = ""
    Dim String_Ka_BxC6 As String = ""
    Dim String_Ka_BzC3 As String = ""
    Dim String_Ka_BxC8 As String = ""
    Dim String_nb_tours As String = ""
    Dim String_deplacement As String = ""
    Dim String_Vbat As String = ""
    Dim pint_string_Aff As Integer = 0
    Dim Datestring As String




    Private Sub Blue_soft_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Timer1.Start()
        Listµpas.Items.Add(1)
        Listµpas.Items.Add(2)
        Listµpas.Items.Add(4)
        Listµpas.Items.Add(8)
        Listµpas.Items.Add(16)
        Listµpas.Items.Add(32)
        Listµpas.SelectedIndex = 5
        ListBox_start_µpas.Items.Add(1)
        ListBox_start_µpas.Items.Add(2)
        ListBox_start_µpas.Items.Add(4)
        ListBox_start_µpas.Items.Add(8)
        ListBox_start_µpas.Items.Add(16)
        ListBox_start_µpas.Items.Add(32)
        ListBox_start_µpas.SelectedIndex = 5


        SerialPort1.Close()
        SerialPort2.Close()

        Datestring = Now.ToString()
        TextBox_Start_s.Text = "200"
        TextBox_start_angle.Text = "3"

        Menu_mainboard(False)
        Menu_Arduino(False)
        Menu_Start(False)
        TextBoxDebug.Visible = False

    End Sub



    Private Sub receive(ByVal sender As System.Object, ByVal e As System.IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort2.DataReceived
        Dim Status As Integer = 1
        Dim cpt As Integer = 0
        Dim cpt1 As Integer = 0
        Dim string1 As String = ""
        Dim string2 As String = ""
        Dim string_value As String = ""

        Dim Difference As Integer = 0
        Dim MessageComplet(500) As Char
        Dim ValeurTemps As Integer = 0
        Dim DebutMessage(500) As Char

        While (Status <> 0)
            SerialPort2.Read(Value, PextValue, 1)
            Valuetest(PintValuetest) = Value(PextValue)
            Inc_Pointeur(PintValuetest, Len(Valuetest))

            If Value(PextValue) = vbLf Then
                Value(PextValue) = vbNullChar
                If PextValue <> 0 Then
                    PextValue = PextValue - 1
                    While Value(PextValue) = vbCr Or Value(PextValue) = vbLf Or Value(PextValue) = " "
                        Value(PextValue) = vbNullChar
                        If PextValue <> 0 Then
                            PextValue = PextValue - 1
                        End If
                    End While
                End If

                If PextValue <> 0 Then

                    MessageComplet = Value

                    For cpt = 0 To 499
                        Message(cpt) = vbNullChar
                    Next

                    cpt = 0
                    While MessageComplet(cpt) <> ";" And MessageComplet(cpt) <> vbNullChar
                        Message(cpt) = MessageComplet(cpt)
                        cpt = cpt + 1

                    End While

                    cpt = 0
                    cpt1 = 0
                    init_buffer_Message_protocol()
                    While Message(cpt) <> "[" And Message(cpt) <> vbNullChar
                        If Message(cpt) = ":" Then
                            cpt1 = 0
                            Message_protocol(0) = vbNullChar
                        Else
                            Message_protocol(cpt1) = Message(cpt)

                            cpt1 = cpt1 + 1
                        End If
                        cpt = cpt + 1
                    End While
                    Message_protocol(cpt1) = vbNullChar
                    string2 = Message_protocol
                    string1 = Message

                    string_Aff(pint_string_Aff) = Value
                    Inc_Pointeur(pint_string_Aff, 500)

                    If StrComp(string2, "Angle.getAngle1", 1) = 0 Then
                        Aff_valeur(string_angle1)

                    ElseIf StrComp(string2, "Angle.getAngle2", 1) = 0 Then
                        Aff_valeur(string_angle2)

                    ElseIf StrComp(string2, "Mag.getxyz", 1) = 0 Then


                        Aff_valeurxyz(string_magx, string_magy, string_magz)
                    ElseIf StrComp(string2, "Count.getId", 1) = 0 Then
                        Aff_valeur(string_value)
                        string_counbterId = string_value

                    ElseIf StrComp(string2, "Algo.getK_common", 1) = 0 Then
                        Aff_valeur(String_K_common)
                    ElseIf StrComp(string2, "Algo.getAngle_2_offset", 1) = 0 Then
                        Aff_valeur(String_Angle_2_offset)
                    ElseIf StrComp(string2, "Algo.getx_0_init", 1) = 0 Then
                        Aff_valeur(String_x_0_init)
                    ElseIf StrComp(string2, "Algo.getx_0_offset", 1) = 0 Then
                        Aff_valeur(String_x_0_offset)
                    ElseIf StrComp(string2, "Algo.getKa_BxC3", 1) = 0 Then
                        Aff_valeur(String_Ka_BxC3)
                    ElseIf StrComp(string2, "Algo.getKb_BxC3", 1) = 0 Then
                        Aff_valeur(String_Ka_BxC4)
                    ElseIf StrComp(string2, "Algo.getKa_ByC3", 1) = 0 Then
                        Aff_valeur(String_Ka_ByC3)
                    ElseIf StrComp(string2, "Algo.getKb_ByC3", 1) = 0 Then
                        Aff_valeur(String_Ka_BxC6)
                    ElseIf StrComp(string2, "Algo.getKa_BzC3", 1) = 0 Then
                        Aff_valeur(String_Ka_BzC3)
                    ElseIf StrComp(string2, "Algo.getKb_BzC3", 1) = 0 Then
                        Aff_valeur(String_Ka_BxC8)
                    ElseIf StrComp(string2, "Algo.getNb_tour", 1) = 0 Then
                        Aff_valeur(String_nb_tours)
                    ElseIf StrComp(string2, "Algo.getPosition", 1) = 0 Then
                        Aff_valeur(String_deplacement)
                    ElseIf StrComp(string2, "Main.getbat", 1) = 0 Then
                        Aff_valeur(String_Vbat)


                    Else

                    End If
                    PextValue = 0
                    init_buffer_value()
                End If
            Else
                If Value(PextValue) = "#" Then
                    Value(PextValue) = ""
                    PextValue = 0
                Else
                    PextValue = PextValue + 1
                    If PextValue >= 1000 Then PextValue = 0
                End If
            End If
            If SerialPort2.IsOpen = True Then
                Status = SerialPort2.BytesToRead()
            Else
                Status = 0
            End If
        End While
    End Sub


    Private Sub wait(ByVal interval As Integer)
        Dim sw As New Stopwatch
        sw.Start()
        Do While sw.ElapsedMilliseconds < interval
            ' Allows UI to remain responsive
            Application.DoEvents()
        Loop
        sw.Stop()
    End Sub
    Sub GetSerialPortNames()
        Dim i As Integer
        If SerialPort2.IsOpen = False Then
            ListBox3.Items.Clear()

            For Each sp As String In My.Computer.Ports.SerialPortNames
                If sp <> PORT1 Then
                    ListBox3.Items.Add(sp)
                End If

            Next
        End If
        If SerialPort1.IsOpen = False Then
            ListComMoteur.Items.Clear()
            For Each sp As String In My.Computer.Ports.SerialPortNames
                If sp <> PORT2 Then
                    ListComMoteur.Items.Add(sp)
                End If
            Next
        End If
    End Sub
    Private Sub Button11_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        MessageCommande = ""
        SerialPort2.Write("##H,N,C:Count.getId" + vbCr)
        wait(1000)
    End Sub
    Private Sub ListBox3_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ListBox3.SelectedIndexChanged
        Dim Baud As Integer
        Dim Name As String
        Dim valueString As String
        Timer1.Stop()
        Angle1.Text = ""
        Angle2.Text = ""
        MagX1.Text = ""
        If ListBox3.SelectedItem <> "" Then
            If SerialPort2.IsOpen = True Then
                SerialPort2.Close()
            End If
            SerialPort2.PortName = ListBox3.SelectedItem
            PORT2 = ListBox3.SelectedItem
            SerialPort2.Handshake = Ports.Handshake.None
            SerialPort2.BaudRate = 115200
            SerialPort2.DataBits = 8
            SerialPort2.Parity = Ports.Parity.None
            SerialPort2.Open()
            Baud = SerialPort2.ReceivedBytesThreshold()
            Baud = SerialPort2.BaudRate()
            Name = SerialPort2.PortName()
            SerialPort2.Write(vbCr)
            wait(200)
            string_counbterId = ""

            SerialPort2.Write("##H,N,C:Count.getId" + vbCr)
            wait(200)


            If string_counbterId <> "" Then
                Menu_mainboard(True)
                If SerialPort1.IsOpen = True Then
                    Menu_Start(True)
                    ListComMoteur.Visible = False
                    ListBox3.Visible = False
                Else
                    Timer1.Start()
                End If
                Timer4.Interval = 50
                Timer4.Start()
                aff_param()


            End If
        Else
            SerialPort2.Close()
        End If
    End Sub
    Private Sub Inc_Pointeur(ByRef Pint As Integer, ByVal size As Integer)
        Pint = Pint + 1
        If Pint >= size Then
            Pint = 0
        End If
    End Sub

    Private Sub init_buffer_value()
        Dim cpt As Integer = 0
        For cpt = 0 To (Len(Value) - 1)
            Value(cpt) = vbNullChar
        Next
    End Sub

    Private Sub init_buffer_Message_protocol()
        Dim cpt As Integer = 0
        For cpt = 0 To (Len(Message_protocol) - 1)
            Message_protocol(cpt) = vbNullChar
        Next
    End Sub

    Private Sub Aff_valeur(ByRef st As String)
        Dim cpt As Integer = 0
        Dim cpt1 As Integer = 0
        cpt = 0
        cpt1 = 0
        init_buffer_Message_protocol()
        While Message(cpt) <> "[" And Message(cpt) <> vbNullChar
            cpt = cpt + 1
        End While
        If Message(cpt) <> vbNullChar Then

            cpt = cpt + 1

            While Message(cpt) <> "]" And Message(cpt) <> "," And Message(cpt) <> vbNullChar
                Message_protocol(cpt1) = Message(cpt)
                cpt1 = cpt1 + 1
                cpt = cpt + 1
            End While

            'string2 = Message_protocol
            'MessageProtocolstring = Message_protocol

            st = Message_protocol

        Else
            st = ""

        End If
    End Sub
    Private Sub Aff_valeurxyz(ByRef stx As String, ByRef sty As String, ByRef stz As String)
        Dim cpt As Integer = 0
        Dim cpt1 As Integer = 0


        cpt = 0
        cpt1 = 0
        init_buffer_Message_protocol()
        While Message(cpt) <> "[" And Message(cpt) <> vbNullChar
            cpt = cpt + 1
        End While
        If Message(cpt) <> vbNullChar Then

            cpt = cpt + 1

            While Message(cpt) <> "]" And Message(cpt) <> "," And Message(cpt) <> vbNullChar
                Message_protocol(cpt1) = Message(cpt)
                cpt1 = cpt1 + 1
                cpt = cpt + 1
            End While

            stx = Message_protocol

            cpt = cpt + 1
            cpt1 = 0
            init_buffer_Message_protocol()
            While Message(cpt) <> "]" And Message(cpt) <> "," And Message(cpt) <> vbNullChar
                Message_protocol(cpt1) = Message(cpt)
                cpt1 = cpt1 + 1
                cpt = cpt + 1
            End While
            sty = Message_protocol


            cpt = cpt + 1
            cpt1 = 0
            init_buffer_Message_protocol()
            While Message(cpt) <> "]" And Message(cpt) <> "," And Message(cpt) <> vbNullChar
                Message_protocol(cpt1) = Message(cpt)
                cpt1 = cpt1 + 1
                cpt = cpt + 1
            End While
            stz = Message_protocol

        End If

    End Sub

    Private Sub Timer4_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer4.Tick
        Timer4.Stop()
        If string_angle1 <> "" Then
            Angle1.Text = string_angle1
            Angle1.BackColor = Color.LawnGreen
        End If

        If string_angle2 <> "" Then
            Angle2.Text = string_angle2
            Angle2.BackColor = Color.LawnGreen
        End If

        If string_magx <> "" Then
            MagX1.Text = string_magx
            MagX1.BackColor = Color.LawnGreen
        End If

        If string_magy <> "" Then
            Magy.Text = string_magy
            Magy.BackColor = Color.LawnGreen
        End If
        If string_magz <> "" Then
            Magz.Text = string_magz
            Magz.BackColor = Color.LawnGreen
        End If
        If String_K_common <> "" Then
            TextBox_K_common_W.Text = String_K_common
            TextBox_K_common_W.BackColor = Color.LawnGreen
            String_K_common = ""
        End If
        If String_Angle_2_offset <> "" Then
            TextBox_Angle_2_offset_W.Text = String_Angle_2_offset
            TextBox_Angle_2_offset_W.BackColor = Color.LawnGreen
            String_Angle_2_offset = ""
        End If
        If String_x_0_init <> "" Then
            TextBox_x_0_init_W.Text = String_x_0_init
            TextBox_x_0_init_W.BackColor = Color.LawnGreen
            String_x_0_init = ""
        End If
        If String_x_0_offset <> "" Then
            TextBox_x_0_offset_W.Text = String_x_0_offset
            TextBox_x_0_offset_W.BackColor = Color.LawnGreen
            String_x_0_offset = ""
        End If
        If String_Ka_BxC3 <> "" Then
            TextBox_Ka_BxC3_W.Text = String_Ka_BxC3
            TextBox_Ka_BxC3_W.BackColor = Color.LawnGreen
            String_Ka_BxC3 = ""
        End If
        If String_Ka_BxC4 <> "" Then
            TextBox_Ka_BxC4_W.Text = String_Ka_BxC4
            TextBox_Ka_BxC4_W.BackColor = Color.LawnGreen
            String_Ka_BxC4 = ""
        End If
        If String_Ka_ByC3 <> "" Then
            TextBox_Ka_ByC3_W.Text = String_Ka_ByC3
            TextBox_Ka_ByC3_W.BackColor = Color.LawnGreen
            String_Ka_ByC3 = ""
        End If
        If String_Ka_BxC6 <> "" Then
            TextBox_Ka_BxC6_W.Text = String_Ka_BxC6
            TextBox_Ka_BxC6_W.BackColor = Color.LawnGreen
            String_Ka_BxC6 = ""
        End If
        If String_Ka_BzC3 <> "" Then
            TextBox_Ka_BzC3_W.Text = String_Ka_BzC3
            TextBox_Ka_BzC3_W.BackColor = Color.LawnGreen
            String_Ka_BzC3 = ""
        End If
        If String_Ka_BxC8 <> "" Then
            TextBox_Ka_BxC8_W.Text = String_Ka_BxC8
            TextBox_Ka_BxC8_W.BackColor = Color.LawnGreen
            String_Ka_BxC8 = ""
        End If

        If string_counbterId <> "" Then
            Label_ID.Text = string_counbterId
            Label_ID.BackColor = Color.LawnGreen
            string_counbterId = ""
        End If

        If String_nb_tours <> "" Then
            TextBox_nb_tours.Text = String_nb_tours
            TextBox_nb_tours.BackColor = Color.LawnGreen
            String_nb_tours = ""
        End If

        If String_Vbat <> "" Then
            TextBat.Text = String_Vbat
            TextBat.BackColor = Color.LawnGreen
            String_Vbat = ""
        End If
        If String_deplacement <> "" Then
            TextBox_deplacement.Text = String_deplacement
            TextBox_deplacement.BackColor = Color.LawnGreen
            String_deplacement = ""
        End If

        SerialPort2.Write("##H,N,C:Angle.getAngle1" + vbCr)
        SerialPort2.Write("##H,N,C:Angle.getAngle2" + vbCr)
        SerialPort2.Write("##H,N,C:Mag.getxyz" + vbCr)
        SerialPort2.Write("##H,N,C:Algo.getNb_tour" + vbCr)
        SerialPort2.Write("##H,N,C:Algo.getPosition" + vbCr)


        Timer4.Start()
    End Sub


    Private Sub Button28_Click(sender As Object, e As EventArgs) Handles ButtonAngle1.Click
        SerialPort2.Write("##H,N,C:Angle.getAngle1" + vbCr)
    End Sub

    Private Sub ButtonAbgle2_Click(sender As Object, e As EventArgs) Handles ButtonAbgle2.Click
        SerialPort2.Write("##H,N,C:Angle.getAngle2" + vbCr)
    End Sub

    Private Sub Mag_Click(sender As Object, e As EventArgs) Handles Mag.Click
        SerialPort2.Write("##H,N,C:Mag.getxyz" + vbCr)
    End Sub

    Private Sub ListComMoteur_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ListComMoteur.SelectedIndexChanged
        Dim Nb As Integer = 1
        Dim c(10) As Char

        Timer1.Stop()
        If ListComMoteur.SelectedItem <> "" Then
            If SerialPort1.IsOpen = True Then
                SerialPort1.Close()
            End If
            SerialPort1.PortName = ListComMoteur.SelectedItem
            PORT1 = ListComMoteur.SelectedItem
            SerialPort1.Handshake = Ports.Handshake.None
            SerialPort1.BaudRate = 115200
            SerialPort1.DataBits = 8
            SerialPort1.Parity = Ports.Parity.None
            SerialPort1.Open()
            wait(100)
            SerialPort1.Write(vbLf)
            Nb = SerialPort1.BytesToRead()
            '       While (Nb <> 0)
            SerialPort1.Read(Value_moteur, PextValue_moteur, Nb)
            PextValue_moteur = 0
            wait(100)
            SerialPort1.Write("?" + vbLf)
            wait(100)
            SerialPort1.Read(c, 0, 1)
            c(1) = vbNullChar

            If (c(0) = "e") Then
                Label_Arduino_ID.Text = "Arduino Connected"
                Label_Arduino_ID.BackColor = Color.LawnGreen
                Menu_Arduino(True)
                If SerialPort2.IsOpen = True Then
                    Menu_Start(True)
                    ListComMoteur.Visible = False
                    ListBox3.Visible = False
                Else
                    Timer1.Start()
                End If
            Else
                SerialPort1.Close()
                SerialPort1.PortName = ""
                ListComMoteur.SelectedItem = ""
            End If
        End If
    End Sub

    Private Sub Send_commande_Rotate_Moteur(ByVal NbDeµPas As String, ByRef AngleCodeur As String)
        Dim Nb As Integer = 0
        Dim Buffer(100) As Char
        Dim ind_fin = False
        Dim i As Integer = 0
        Dim ValueString As String = ""

        SerialPort1.Write("r" + NbDeµPas + vbLf)
        While (ind_fin = False)
            While (Nb <> 0)
                SerialPort1.Read(Buffer, i, 1)
                If (Buffer(i) = vbLf) Or (Buffer(i) = vbCr) Then
                    Buffer(i) = vbNullChar
                    Trait_commande_Moteur(Buffer, ValueString)

                    If ValueString <> vbNullString Then
                        AngleCodeur = ValueString
                        ind_fin = True
                    End If
                    i = 0
                Else
                    Inc_Pointeur(i, Len(Buffer))
                End If
                Nb = Nb - 1
            End While

            Nb = SerialPort1.BytesToRead()
        End While
    End Sub


    Private Sub Trait_commande_Moteur(ByVal Buffer() As Char, ByRef reponse As String)

        Dim i As Integer = 0

        If (Buffer(0) = "r") Then
        ElseIf (Buffer(0) = "a") Then
            If (IsNumeric(Buffer(1)) = True) Then

            ElseIf (Buffer(1) = "c") Then
                If (IsNumeric(Buffer(2)) = True) Or (Buffer(2) = "-" And IsNumeric(Buffer(3)) = True) Then


                    While (Buffer(i) <> vbNullChar)
                        Buffer(i) = Buffer(i + 2)
                        i = i + 1
                    End While
                    Buffer(i) = vbNullChar
                    reponse = Buffer

                End If
            Else
            End If
        ElseIf (Buffer(0) = "c") Then
            If (IsNumeric(Buffer(1)) = True) Then

                reponse = Buffer

                While (Buffer(i) <> vbNullChar)
                    Buffer(i) = Buffer(i + 1)
                    i = i + 1
                End While
                Buffer(i) = vbNullChar
                reponse = Buffer


            End If

        ElseIf (Buffer(0) = "m") Then
            If (IsNumeric(Buffer(1)) = True) Then
                While (Buffer(i) <> vbNullChar)
                    Buffer(i) = Buffer(i + 1)
                    i = i + 1
                End While
                Buffer(i) = vbNullChar
                reponse = Buffer
            End If

        ElseIf (Buffer(0) = "s") Then
            If (IsNumeric(Buffer(1)) = True) Then
                While (Buffer(i) <> vbNullChar)
                    Buffer(i) = Buffer(i + 1)
                    i = i + 1
                End While
                Buffer(i) = vbNullChar
                reponse = Buffer
            End If

        ElseIf (Buffer(0) = "z") Then
            If (IsNumeric(Buffer(1)) = True) Then
                While (Buffer(i) <> vbNullChar)
                    Buffer(i) = Buffer(i + 1)
                    i = i + 1
                End While
                Buffer(i) = vbNullChar
                reponse = Buffer
            End If
        ElseIf (Buffer(0) = "e") Then
        End If
    End Sub

    Private Sub ButtonCodeur_Click(sender As Object, e As EventArgs) Handles ButtonCodeur.Click
        Dim ValueString As String
        Send_commande_Codeur_Moteur(ValueString)
        TextBox_Codeur.Text = ValueString
    End Sub


    Private Sub Send_commande_Codeur_Moteur(ByRef AngleCodeur As String)
        Dim Nb As Integer = 0
        Dim Buffer(100) As Char
        Dim ind_fin = False
        Dim i As Integer = 0
        Dim ValueString As String = ""

        SerialPort1.Write("c" + vbLf)

        While (ind_fin = False)
            While (Nb <> 0)
                SerialPort1.Read(Buffer, i, 1)
                If (Buffer(i) = vbLf) Or (Buffer(i) = vbCr) Then
                    Buffer(i) = vbNullChar
                    Trait_commande_Moteur(Buffer, ValueString)

                    If ValueString <> vbNullString Then
                        AngleCodeur = ValueString
                        ind_fin = True
                    End If
                    i = 0
                Else
                    Inc_Pointeur(i, Len(Buffer))
                End If
                Nb = Nb - 1
            End While

            Nb = SerialPort1.BytesToRead()

        End While



    End Sub


    Private Sub Send_commande_µpas_Moteur(ByRef µpas As String, ByRef reponse As String)
        Dim Nb As Integer = 0
        Dim Buffer(100) As Char
        Dim ind_fin = False
        Dim i As Integer = 0
        Dim ValueString As String = ""

        SerialPort1.Write("m" + µpas + vbLf)

        While (ind_fin = False)
            While (Nb <> 0)
                SerialPort1.Read(Buffer, i, 1)
                If (Buffer(i) = vbLf) Or (Buffer(i) = vbCr) Then
                    Buffer(i) = vbNullChar
                    Trait_commande_Moteur(Buffer, ValueString)

                    If ValueString <> vbNullString Then
                        reponse = ValueString
                        ind_fin = True
                    End If
                    i = 0
                Else
                    Inc_Pointeur(i, Len(Buffer))
                End If
                Nb = Nb - 1
            End While

            Nb = SerialPort1.BytesToRead()

        End While



    End Sub


    Private Sub Send_commande_s_Moteur(ByVal vitesse As String, ByRef reponse As String)
        Dim Nb As Integer = 0
        Dim Buffer(100) As Char
        Dim ind_fin = False
        Dim i As Integer = 0
        Dim ValueString As String = ""

        SerialPort1.Write("s" + vitesse + vbLf)

        While (ind_fin = False)
            While (Nb <> 0)
                SerialPort1.Read(Buffer, i, 1)
                If (Buffer(i) = vbLf) Or (Buffer(i) = vbCr) Then
                    Buffer(i) = vbNullChar
                    Trait_commande_Moteur(Buffer, ValueString)

                    If ValueString <> vbNullString Then
                        ind_fin = True
                        reponse = ValueString
                    End If
                    i = 0
                Else
                    Inc_Pointeur(i, Len(Buffer))
                End If
                Nb = Nb - 1
            End While

            Nb = SerialPort1.BytesToRead()

        End While



    End Sub


    Private Sub Send_commande_Reset_Codeur_Moteur(ByRef reponse As String)
        Dim Nb As Integer = 0
        Dim Buffer(100) As Char
        Dim ind_fin = False
        Dim i As Integer = 0
        Dim ValueString As String = ""

        SerialPort1.Write("z" + vbLf)

        While (ind_fin = False)
            While (Nb <> 0)
                SerialPort1.Read(Buffer, i, 1)
                If (Buffer(i) = vbLf) Or (Buffer(i) = vbCr) Then
                    Buffer(i) = vbNullChar
                    Trait_commande_Moteur(Buffer, ValueString)

                    If ValueString <> vbNullString Then
                        ind_fin = True
                        reponse = ValueString
                    End If
                    i = 0
                Else
                    Inc_Pointeur(i, Len(Buffer))
                End If
                Nb = Nb - 1
            End While

            Nb = SerialPort1.BytesToRead()

        End While



    End Sub


    Private Sub M_Moteur_Click(sender As Object, e As EventArgs) Handles M_Moteur.Click
        Dim Reponse As String = ""
        Send_commande_µpas_Moteur(Listµpas.SelectedItem, Reponse)

        TextBox_Reponse_m.Text = Reponse

    End Sub

    Private Sub Button_S_Moteur_Click(sender As Object, e As EventArgs) Handles Button_S_Moteur.Click
        Dim Reponse As String = ""
        Dim SpeedMoteur As Integer
        If TextBoxSMoteur.Text <> "" Then
            SpeedMoteur = CInt(TextBoxSMoteur.Text)
            If SpeedMoteur > 0 And SpeedMoteur <= 400 Then
                Send_commande_s_Moteur(TextBoxSMoteur.Text, Reponse)
                TextBox_reponse_s.Text = Reponse
            Else
                TextBox_reponse_s.Text = "erreur"
            End If
        Else
            TextBox_reponse_s.Text = "erreur"
        End If

    End Sub

    Private Sub Button_Z_codeur_Click(sender As Object, e As EventArgs) Handles Button_Z_codeur.Click
        Dim ValueString As String


        Send_commande_Reset_Codeur_Moteur(ValueString)
        TextBox_Codeur.Text = ValueString
    End Sub
    Private Sub R_Moteur_Click(sender As Object, e As EventArgs) Handles R_Moteur.Click
        Dim ValueString As String
        If TextBox_R_Moteur.Text() <> "" Then
            Send_commande_Rotate_Moteur(TextBox_R_Moteur.Text(), ValueString)
        Else
            ValueString = "erreur"
        End If
        TextBox_Codeur.Text = ValueString
    End Sub


    Private Sub Read_Mag(ByRef x As String, ByRef y As String, ByRef z As String)
        string_magx = ""
        string_magy = ""
        string_magz = ""
        SerialPort2.Write("##H,N,C:Mag.getxyz" + vbCr)
        While (string_magx = "" Or string_magy = "" Or string_magz = "")

        End While

        x = string_magx
        y = string_magy
        z = string_magz


    End Sub


    Private Sub Read_Angle(ByRef Angle1 As String, ByRef Angle2 As String)
        string_angle1 = ""
        string_angle2 = ""

        SerialPort2.Write("##H,N,C:Angle.getAngle1" + vbCr)
        SerialPort2.Write("##H,N,C:Angle.getAngle2" + vbCr)

        While (string_angle1 = "" Or string_angle2 = "")
        End While

        Angle1 = string_angle1
        Angle2 = string_angle2
    End Sub


    Private Sub AngleToµPas(ByVal Angle As String, ByVal pas As Integer, ByRef µpas As Integer)


        µpas = pas * 200 * 60 * Angle / 360

    End Sub


    Private Sub AngleToµPas(ByVal Nb_µpas_Moteur As Integer, ByRef Angle_Codeur As String, ByRef X As String, ByRef Y As String, ByRef Z As String, ByRef Angle1 As String, ByRef Angle2 As String)


        Dim Reponse As String


        Debug_log(vbCrLf + "Deplacement Moteur=" + Nb_µpas_Moteur.ToString)
        Send_commande_Rotate_Moteur(Nb_µpas_Moteur.ToString, Reponse)
        Angle_Codeur = Reponse
        Debug_log(vbCrLf + "Deplacement Moteur=" + Reponse)
        wait(100)

        Debug_log(vbCrLf + "Read Mag")
        Read_Mag(X, Y, Z)
        Debug_log(vbCrLf + "X=" + X)
        Debug_log(" Y=" + Y)
        Debug_log(" Z=" + Z)

        Debug_log(vbCrLf + "Read Angle")
        Read_Angle(Angle1, Angle2)
        Debug_log(vbCrLf + "Angle1=" + Angle1)
        Debug_log(" Angle2=" + Angle2)
    End Sub




    Private Sub StartMesure_Click(sender As Object, e As EventArgs) Handles StartMesure.Click
        Dim ValueString As String
        Dim X As String = ""
        Dim Y As String = ""
        Dim Z As String = ""


        Dim Angle1 As String = ""
        Dim Angle2 As String = ""
        Dim Angle As String = ""
        Dim Reponse As String = ""

        Dim Vitesse_Moteur As Integer = CInt(TextBox_Start_s.Text)
        Dim Pas_Moteur As Integer = CInt(ListBox_start_µpas.SelectedItem)
        Dim Angle_Moteur As Integer = CInt(TextBox_start_angle.Text)
        Dim Nb_µpas_Moteur As Integer = (200 * 60 * Pas_Moteur * Angle_Moteur) / 360

        Dim AngleCourantDuMoteur As Integer
        Dim Angle_Codeur As String

        Dim i As Integer

        Timer4.Stop()
        Menu_mainboard(False)
        Menu_Arduino(False)
        TextBoxDebug.Visible = True
        If NameFile_log = "" Then
            NameFile_log = "C:\test_compteur\" + "Etal" + Now.Year.ToString + "-" + Now.Month.ToString + "-" + Now.Day.ToString + " " + Now.Hour.ToString + " " + Now.Minute.ToString + " " + Now.Second.ToString + ".csv"



            Dim SW As StreamWriter = File.AppendText(NameFile_log)
            SW.Write("Angle Moteur" + ";" + "Angle Codeur" + ";" + "Angle 1" + ";" + "Angle 2" + ";" + "Mag X" + ";" + "Mag Y" + ";" + "Mag Z" + vbCr)
            SW.Close()
        End If

        TextBoxDebug.AppendText(vbCrLf + "start")

        ' AngleToµPas(Angle_Moteur, Pas_Moteur, Nb_µpas_Moteur)

        'configuration

        ' Vitesse à 200tr/min
        Debug_log(vbCrLf + "Vitesse=" + Vitesse_Moteur.ToString)
        Debug_log("tr/min")
        Send_commande_s_Moteur(TextBox_Start_s.Text, Reponse)
        Debug_log(vbCrLf + "Vitesse=" + Reponse)
        Debug_log("tr/min")

        Debug_log(vbCrLf + "Pas moteur=" + Pas_Moteur.ToString)
        Send_commande_µpas_Moteur(ListBox_start_µpas.SelectedItem, Reponse)
        Debug_log(vbCrLf + "Pas moteur=" + Reponse)

        'ratrapage de jeu 10 degré

        AngleToµPas(-Nb_µpas_Moteur / Angle_Moteur * 10, Angle_Codeur, X, Y, Z, Angle1, Angle2)
        AngleToµPas(Nb_µpas_Moteur / Angle_Moteur * 10, Angle_Codeur, X, Y, Z, Angle1, Angle2)

        Send_commande_Reset_Codeur_Moteur(Angle_Codeur)
        AngleCourantDuMoteur = 0

        'Init
        Debug_log(vbCrLf + "Reset Codeur")
        Send_commande_Reset_Codeur_Moteur(ValueString)
        Debug_log(vbCrLf + "Value Codeur = " + ValueString)
        Debug_log(vbCrLf + "Read Mag")
        Read_Mag(X, Y, Z)
        wait(100)

        Debug_log(vbCrLf + "X=" + X)
        Debug_log(" Y=" + Y)
        Debug_log(" Z=" + Z)

        Debug_log(vbCrLf + "Read Angle")
        Read_Angle(Angle1, Angle2)
        Debug_log(vbCrLf + "Angle1=" + Angle1)
        Debug_log(" Angle2=" + Angle2)

        If NameFile_log <> "" Then
            Dim SW As StreamWriter = File.AppendText(NameFile_log)
            SW.Write(AngleCourantDuMoteur.ToString + ";" + Angle_Codeur + ";" + Angle1 + ";" + Angle2 + ";" + X + ";" + Y + ";" + Z + vbCr)
            SW.Close()
        End If
        TextBoxDebug.AppendText(vbCrLf + AngleCourantDuMoteur.ToString)
        TextBoxDebug.AppendText("---" + Angle_Codeur)
        TextBoxDebug.AppendText("---" + Angle1)
        TextBoxDebug.AppendText("---" + Angle2)
        TextBoxDebug.AppendText("---" + X)
        TextBoxDebug.AppendText("---" + Y)
        TextBoxDebug.AppendText("---" + Z)

        ' touner de 3 degrés et faire les mesure mag et angles

        For i = 1 To ((360 * 12) / CInt(TextBox_start_angle.Text))
            AngleToµPas(Nb_µpas_Moteur, Angle_Codeur, X, Y, Z, Angle1, Angle2)
            AngleCourantDuMoteur = AngleCourantDuMoteur + Angle_Moteur
            Read_Mag(X, Y, Z)

            If NameFile_log <> "" Then
                Dim SW As StreamWriter = File.AppendText(NameFile_log)
                SW.Write(AngleCourantDuMoteur.ToString + ";" + Angle_Codeur + ";" + Angle1 + ";" + Angle2 + ";" + X + ";" + Y + ";" + Z + vbCr)
                SW.Close()
            End If
            Debug_log(vbCrLf + " Angle_Moteur=" + AngleCourantDuMoteur.ToString)
            TextBoxDebug.AppendText(vbCrLf + AngleCourantDuMoteur.ToString)
            TextBoxDebug.AppendText("---" + Angle_Codeur)
            TextBoxDebug.AppendText("---" + Angle1)
            TextBoxDebug.AppendText("---" + Angle2)
            TextBoxDebug.AppendText("---" + X)
            TextBoxDebug.AppendText("---" + Y)
            TextBoxDebug.AppendText("---" + Z)
        Next
        Menu_mainboard(True)
        Menu_Arduino(True)
        TextBoxDebug.Visible = False
        Timer4.Start()
    End Sub


    Private Sub Debug_log(String_value As String)
        If debug <> "" Then
            TextBoxDebug.AppendText(String_value)
        End If
    End Sub
    Private Sub Menu_mainboard(value As Boolean)
        ButtonAngle1.Visible = value
        ButtonAbgle2.Visible = value
        Mag.Visible = value
        Angle1.Visible = value
        Angle2.Visible = value
        MagX1.Visible = value
        Magy.Visible = value
        Magz.Visible = value
        Label5.Visible = value
        Label6.Visible = value
        Label7.Visible = value
    End Sub

    Private Sub Menu_Arduino(value As Boolean)
        R_Moteur.Visible = value
        M_Moteur.Visible = value
        Button_S_Moteur.Visible = value
        Button_Z_codeur.Visible = value
        ButtonCodeur.Visible = value
        TextBox_R_Moteur.Visible = value
        TextBox_Codeur.Visible = value
        TextBox_Reponse_m.Visible = value
        Listµpas.Visible = value
        TextBoxSMoteur.Visible = value
        TextBox_reponse_s.Visible = value
    End Sub

    Private Sub Menu_Start(value As Boolean)
        StartMesure.Visible = value
        TextBox_start_angle.Visible = value
        Label1.Visible = value
        TextBox_Start_s.Visible = value
        Label3.Visible = value
        ListBox_start_µpas.Visible = value
        Label4.Visible = value
        'TextBoxDebug.Visible = value
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        GetSerialPortNames()
    End Sub

    Private Sub K_common_Click(sender As Object, e As EventArgs) Handles K_common.Click
        SerialPort2.Write("##H,N,C:Algo.getK_common" + vbCr)
        'Timer4.Stop()
    End Sub

    Private Sub K_common_w_Click(sender As Object, e As EventArgs) Handles K_common_w.Click
        If TextBox_K_common_W.Text() <> "" Then
            SerialPort2.Write("##H,N,C:Algo.setK_common=")
            SerialPort2.Write(TextBox_K_common_W.Text)
            SerialPort2.Write(vbCr)
            SerialPort2.Write("##H,N,C:Algo.getK_common" + vbCr)

        Else
            TextBox_K_common_W.Text = "erreur"
        End If
    End Sub

    Private Sub Angle_2_offset_Click(sender As Object, e As EventArgs) Handles Angle_2_offset.Click
        SerialPort2.Write("##H,N,C:Algo.getAngle_2_offset" + vbCr)
    End Sub

    Private Sub x_0_init_Click(sender As Object, e As EventArgs) Handles x_0_init.Click
        SerialPort2.Write("##H,N,C:Algo.getx_0_init" + vbCr)
    End Sub

    Private Sub x_0_offset_Click(sender As Object, e As EventArgs) Handles x_0_offset.Click
        SerialPort2.Write("##H,N,C:Algo.getx_0_offset" + vbCr)
    End Sub

    Private Sub Ka_BxC3_Click(sender As Object, e As EventArgs) Handles Ka_BxC3.Click
        SerialPort2.Write("##H,N,C:Algo.getKa_BxC3" + vbCr)
    End Sub

    Private Sub Ka_BxC4_Click(sender As Object, e As EventArgs) Handles Ka_BxC4.Click
        SerialPort2.Write("##H,N,C:Algo.getKb_BxC3" + vbCr)
    End Sub

    Private Sub Ka_ByC3_Click(sender As Object, e As EventArgs) Handles Ka_ByC3.Click
        SerialPort2.Write("##H,N,C:Algo.getKa_ByC3" + vbCr)
    End Sub

    Private Sub Ka_BxC6_Click(sender As Object, e As EventArgs) Handles Ka_BxC6.Click
        SerialPort2.Write("##H,N,C:Algo.getKb_ByC3" + vbCr)
    End Sub

    Private Sub Ka_BzC3_Click(sender As Object, e As EventArgs) Handles Ka_BzC3.Click
        SerialPort2.Write("##H,N,C:Algo.getKa_BzC3" + vbCr)
    End Sub

    Private Sub Ka_BxC8_Click(sender As Object, e As EventArgs) Handles Ka_BxC8.Click
        SerialPort2.Write("##H,N,C:Algo.getKb_BzC3" + vbCr)
    End Sub

    Private Sub Angle_2_offset_W_Click(sender As Object, e As EventArgs) Handles Angle_2_offset_W.Click
        If TextBox_Angle_2_offset_W.Text() <> "" Then
            SerialPort2.Write("##H,N,C:Algo.setAngle_2_offset=")
            SerialPort2.Write(TextBox_Angle_2_offset_W.Text)
            SerialPort2.Write(vbCr)
            SerialPort2.Write("##H,N,C:Algo.getAngle_2_offset" + vbCr)
        Else
            TextBox_Angle_2_offset_W.Text = "erreur"
        End If
    End Sub

    Private Sub x_0_init_W_Click(sender As Object, e As EventArgs) Handles x_0_init_W.Click
        If TextBox_x_0_init_W.Text() <> "" Then
            SerialPort2.Write("##H,N,C:Algo.setx_0_init=")
            SerialPort2.Write(TextBox_x_0_init_W.Text)
            SerialPort2.Write(vbCr)
            SerialPort2.Write("##H,N,C:Algo.getx_0_init" + vbCr)
        Else
            TextBox_x_0_init_W.Text = "erreur"
        End If
    End Sub

    Private Sub x_0_offset_W_Click(sender As Object, e As EventArgs) Handles x_0_offset_W.Click
        If TextBox_x_0_offset_W.Text() <> "" Then
            SerialPort2.Write("##H,N,C:Algo.setx_0_offset=")
            SerialPort2.Write(TextBox_x_0_offset_W.Text)
            SerialPort2.Write(vbCr)
            SerialPort2.Write("##H,N,C:Algo.getx_0_offset" + vbCr)
        Else
            TextBox_x_0_offset_W.Text = "erreur"
        End If
    End Sub

    Private Sub Ka_BxC3_W_Click(sender As Object, e As EventArgs) Handles Ka_BxC3_W.Click
        If TextBox_Ka_BxC3_W.Text() <> "" Then
            SerialPort2.Write("##H,N,C:Algo.setKa_BxC3=")
            SerialPort2.Write(TextBox_Ka_BxC3_W.Text)
            SerialPort2.Write(vbCr)
            SerialPort2.Write("##H,N,C:Algo.getKa_BxC3" + vbCr)
        Else
            TextBox_Ka_BxC3_W.Text = "erreur"
        End If
    End Sub

    Private Sub Ka_BxC4_W_Click(sender As Object, e As EventArgs) Handles Ka_BxC4_W.Click
        If TextBox_x_0_offset_W.Text() <> "" Then
            SerialPort2.Write("##H,N,C:Algo.setKb_BxC3=")
            SerialPort2.Write(TextBox_Ka_BxC4_W.Text)
            SerialPort2.Write(vbCr)
            SerialPort2.Write("##H,N,C:Algo.getKb_BxC3" + vbCr)
        Else
            TextBox_Ka_BxC4_W.Text = "erreur"
        End If
    End Sub

    Private Sub Ka_ByC3_W_Click(sender As Object, e As EventArgs) Handles Ka_ByC3_W.Click
        If TextBox_Ka_ByC3_W.Text() <> "" Then
            SerialPort2.Write("##H,N,C:Algo.setKa_ByC3=")
            SerialPort2.Write(TextBox_Ka_ByC3_W.Text)
            SerialPort2.Write(vbCr)
            SerialPort2.Write("##H,N,C:Algo.getKa_ByC3" + vbCr)
        Else
            TextBox_Ka_ByC3_W.Text = "erreur"
        End If
    End Sub

    Private Sub Ka_BxC6_W_Click(sender As Object, e As EventArgs) Handles Ka_BxC6_W.Click
        If TextBox_Ka_BxC6_W.Text() <> "" Then
            SerialPort2.Write("##H,N,C:Algo.setKb_ByC3=")
            SerialPort2.Write(TextBox_Ka_BxC6_W.Text)
            SerialPort2.Write(vbCr)
            SerialPort2.Write("##H,N,C:Algo.getKb_ByC3" + vbCr)
        Else
            TextBox_Ka_BxC6_W.Text = "erreur"
        End If
    End Sub

    Private Sub Ka_BzC3_W_Click(sender As Object, e As EventArgs) Handles Ka_BzC3_W.Click
        If TextBox_Ka_BzC3_W.Text() <> "" Then
            SerialPort2.Write("##H,N,C:Algo.setKa_BzC3=")
            SerialPort2.Write(TextBox_Ka_BzC3_W.Text)
            SerialPort2.Write(vbCr)
            SerialPort2.Write("##H,N,C:Algo.getKa_BzC3" + vbCr)
        Else
            TextBox_Ka_BzC3_W.Text = "erreur"
        End If
    End Sub

    Private Sub Ka_BxC8_W_Click(sender As Object, e As EventArgs) Handles Ka_BxC8_W.Click
        If TextBox_Ka_BxC8_W.Text() <> "" Then
            SerialPort2.Write("##H,N,C:Algo.setKb_BzC3=")
            SerialPort2.Write(TextBox_Ka_BxC8_W.Text)
            SerialPort2.Write(vbCr)
            SerialPort2.Write("##H,N,C:Algo.getKb_BzC3" + vbCr)
        Else
            TextBox_Ka_BxC8_W.Text = "erreur"
        End If
    End Sub
    Private Sub aff_param()
        SerialPort2.Write("##H,N,C:Algo.getK_common" + vbCr)
        SerialPort2.Write("##H,N,C:Algo.getAngle_2_offset" + vbCr)
        SerialPort2.Write("##H,N,C:Algo.getx_0_init" + vbCr)
        SerialPort2.Write("##H,N,C:Algo.getx_0_offset" + vbCr)
        SerialPort2.Write("##H,N,C:Algo.getKa_BxC3" + vbCr)
        SerialPort2.Write("##H,N,C:Algo.getKb_BxC3" + vbCr)
        SerialPort2.Write("##H,N,C:Algo.getKa_ByC3" + vbCr)
        SerialPort2.Write("##H,N,C:Algo.getKb_ByC3" + vbCr)
        SerialPort2.Write("##H,N,C:Algo.getKa_BzC3" + vbCr)
        SerialPort2.Write("##H,N,C:Algo.getKb_BzC3" + vbCr)
    End Sub

    Private Sub Bat_Click(sender As Object, e As EventArgs) Handles Bat.Click
        SerialPort2.Write("##H,N,C:Main.getbat" + vbCr)
    End Sub
End Class

