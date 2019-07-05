# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'cacilho.ui'
#
# Created by: PyQt5 UI code generator 5.12.1
#
# WARNING! All changes made in this file will be lost!

# IMPORTA BIBLIOTECAS
import sys
import serial
from PyQt5 import QtCore, QtGui, QtWidgets

#CONFIGURA PORTA E BAUD RATE
ser = serial.Serial('COM4', 500000)

#DECLARA VARIAVEIS GLOBAIS 
#CADA UMA CONTROLA SE O BOTAO FOI APERTADO OU NAO
global ctrl_5k
global ctrl_2_5k
global ctrl_1_25k
global ctrl_625
global ctrl_312
global ctrl_156
global pp_ctrl
#INICIA VARIAVEIS COMO ZERO
ctrl_5k = 0
ctrl_2_5k = 0
ctrl_1_25k = 0
ctrl_625 = 0
ctrl_312 = 0
ctrl_156 = 0
#VARIAVEL DE CONTROLE DO BOTAO PLAY/PAUSE
pp_ctrl = 0


#CONFIGURAcoes EXPORTADAS DO QT CREATOR
class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(738, 585)
        font = QtGui.QFont()
        font.setPointSize(24)
        Form.setFont(font)
        Form.setContextMenuPolicy(QtCore.Qt.NoContextMenu)
        Form.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.label = QtWidgets.QLabel(Form)
        self.label.setGeometry(QtCore.QRect(50, 20, 671, 71))
        font = QtGui.QFont()
        font.setPointSize(60)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.label_2 = QtWidgets.QLabel(Form)
        self.label_2.setGeometry(QtCore.QRect(10, 90, 711, 81))
        self.label_2.setObjectName("label_2")


        self.freq_5k = QtWidgets.QPushButton(Form)
        self.freq_5k.setGeometry(QtCore.QRect(50, 210, 91, 81))
        font = QtGui.QFont()
        font.setPointSize(16)
        self.freq_5k.setFont(font)
        self.freq_5k.setObjectName("freq_5k")
        #ESTA LINHA NAO VEM IMPORTA, E EH A QUE LINKA A FUNCAO COM O BOTAO
		self.freq_5k.clicked.connect(self.exe_freq_5k)


        self.freq_1_25k = QtWidgets.QPushButton(Form)
        self.freq_1_25k.setGeometry(QtCore.QRect(50, 330, 91, 81))
        font = QtGui.QFont()
        font.setPointSize(16)
        self.freq_1_25k.setFont(font)
        self.freq_1_25k.setObjectName("freq_1_25k")
		#ESTA LINHA NAO VEM IMPORTA, E EH A QUE LINKA A FUNCAO COM O BOTAO
        self.freq_1_25k.clicked.connect(self.exe_freq_1_25k)


        self.freq_312 = QtWidgets.QPushButton(Form)
        self.freq_312.setGeometry(QtCore.QRect(50, 450, 91, 81))
        font = QtGui.QFont()
        font.setPointSize(16)
        self.freq_312.setFont(font)
        self.freq_312.setObjectName("freq_312")
		#ESTA LINHA NAO VEM IMPORTA, E EH A QUE LINKA A FUNCAO COM O BOTAO
        self.freq_312.clicked.connect(self.exe_freq_312)


        self.freq_2_5k = QtWidgets.QPushButton(Form)
        self.freq_2_5k.setGeometry(QtCore.QRect(210, 210, 91, 81))
        font = QtGui.QFont()
        font.setPointSize(16)
        self.freq_2_5k.setFont(font)
        self.freq_2_5k.setObjectName("freq_2_5k")
		#ESTA LINHA NAO VEM IMPORTA, E EH A QUE LINKA A FUNCAO COM O BOTAO
        self.freq_2_5k.clicked.connect(self.exe_freq_2_5k)


        self.freq_625 = QtWidgets.QPushButton(Form)
        self.freq_625.setGeometry(QtCore.QRect(210, 330, 91, 81))
        font = QtGui.QFont()
        font.setPointSize(16)
        self.freq_625.setFont(font)
        self.freq_625.setObjectName("freq_625")
		#ESTA LINHA NAO VEM IMPORTA, E EH A QUE LINKA A FUNCAO COM O BOTAO
        self.freq_625.clicked.connect(self.exe_freq_625)


        self.freq_156 = QtWidgets.QPushButton(Form)
        self.freq_156.setGeometry(QtCore.QRect(210, 450, 91, 81))
        font = QtGui.QFont()
        font.setPointSize(16)
        self.freq_156.setFont(font)
        self.freq_156.setObjectName("freq_156")
		#ESTA LINHA NAO VEM IMPORTA, E EH A QUE LINKA A FUNCAO COM O BOTAO
        self.freq_156.clicked.connect(self.exe_freq_156)


        self.line = QtWidgets.QFrame(Form)
        self.line.setGeometry(QtCore.QRect(370, 180, 20, 401))
        self.line.setSizeIncrement(QtCore.QSize(0, 0))
        self.line.setFrameShadow(QtWidgets.QFrame.Plain)
        self.line.setLineWidth(2)
        self.line.setFrameShape(QtWidgets.QFrame.VLine)
        self.line.setObjectName("line")


        self.som2 = QtWidgets.QPushButton(Form)
        self.som2.setGeometry(QtCore.QRect(610, 210, 91, 81))
        self.som2.setObjectName("som2")
		#ESTA LINHA NAO VEM IMPORTA, E EH A QUE LINKA A FUNCAO COM O BOTAO
        self.som2.clicked.connect(self.exe_som2)


        self.som1 = QtWidgets.QPushButton(Form)
        self.som1.setGeometry(QtCore.QRect(450, 210, 91, 81))
        self.som1.setObjectName("som1")
		#ESTA LINHA NAO VEM IMPORTA, E EH A QUE LINKA A FUNCAO COM O BOTAO
        self.som1.clicked.connect(self.exe_som1)


        self.play_pause = QtWidgets.QPushButton(Form)
        self.play_pause.setGeometry(QtCore.QRect(570, 450, 151, 81))
        self.play_pause.setObjectName("play_pause")
		#ESTA LINHA NAO VEM IMPORTA, E EH A QUE LINKA A FUNCAO COM O BOTAO
        self.play_pause.clicked.connect(self.exe_play_pause)


        self.som3 = QtWidgets.QPushButton(Form)
        self.som3.setGeometry(QtCore.QRect(450, 330, 91, 81))
        self.som3.setObjectName("som3")
		#ESTA LINHA NAO VEM IMPORTA, E EH A QUE LINKA A FUNCAO COM O BOTAO
        self.som3.clicked.connect(self.exe_som3)


        self.prog = QtWidgets.QPushButton(Form)
        self.prog.setGeometry(QtCore.QRect(450, 450, 91, 81))
        self.prog.setObjectName("prog")
		#ESTA LINHA NAO VEM IMPORTA, E EH A QUE LINKA A FUNCAO COM O BOTAO
        self.prog.clicked.connect(self.exe_prog)


        self.som4 = QtWidgets.QPushButton(Form)
        self.som4.setGeometry(QtCore.QRect(610, 330, 91, 81))
        self.som4.setObjectName("som4")
		#ESTA LINHA NAO VEM IMPORTA, E EH A QUE LINKA A FUNCAO COM O BOTAO
        self.som4.clicked.connect(self.exe_som4)

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
		#PROX LINHA ALTERA NOME MOSTRADO NA JANELA
        Form.setWindowTitle(_translate("Form", "GrooveBox - Mk I"))   # <---
        self.label.setText(_translate("Form", "GrooveBox - Mk I"))
        self.label_2.setText(_translate("Form", "Alunos: Gabriel Cacilho Zilio e Tiago Pereira Comin"))
        self.freq_5k.setText(_translate("Form", "5 kHz"))
        self.freq_1_25k.setText(_translate("Form", "1,25 kHz"))
        self.freq_312.setText(_translate("Form", "312 Hz"))
        self.freq_2_5k.setText(_translate("Form", "2,5 kHz"))
        self.freq_625.setText(_translate("Form", "625 Hz"))
        self.freq_156.setText(_translate("Form", "156 Hz"))
        self.som2.setText(_translate("Form", "2"))
        self.som1.setText(_translate("Form", "1"))
        self.play_pause.setText(_translate("Form", "Play/Stop"))
        self.som3.setText(_translate("Form", "3"))
        self.prog.setText(_translate("Form", "Prog"))
        self.som4.setText(_translate("Form", "4"))

#O CODIGO EXPORTADO ACABA NESTA LINHA


	#FUNCOES QUE SAO ACIONADAS PELO CLICK DO BOTAO
	#E ENVIAM OS SINAIS DE CONTROLE PELA UART
    def exe_freq_5k(self):
        global ctrl_5k				#DECLARA QUE UTILIZA VARIAVEL GLOBAL
		
        if ctrl_5k == 0:			#VERIFICA SE BOTAO ESTA DESATIVADO
            ser.write(b'1')			#SE SIM, ENVIA VALOR PARA ATIVAR
            ctrl_5k = 1				#ALTERA VARIAVEL DE CONTROLE
        else:						#SE NAO, ESTA ATIVADO
            ser.write(b'w')			#ENVIA VAR. DE CONTROLE PARA DESATIVAR
            ctrl_5k = 0				#ALTERA VARIAVEL DE CONTROLE
									#PROXS FUNCAO SAO A MESMA LOGICA
    def exe_freq_2_5k(self):
        global ctrl_2_5k

        if ctrl_2_5k == 0:
            ser.write(b'2')
            ctrl_2_5k = 1
        else:
            ser.write(b's')
            ctrl_2_5k = 0

    def exe_freq_1_25k(self):
        global ctrl_1_25k

        if ctrl_1_25k == 0:
            ser.write(b'3')
            ctrl_1_25k = 1
        else:
            ser.write(b'x')
            ctrl_1_25k = 0

    def exe_freq_625(self):
        global ctrl_625
		
        if ctrl_625 == 0:
            ser.write(b'4')
            ctrl_625 = 1
        else:
            ser.write(b'r')
            ctrl_625 = 0
		
    def exe_freq_312(self):
        global ctrl_312
		
        if ctrl_312 == 0:
            ser.write(b'5')
            ctrl_312 = 1
        else:
            ser.write(b'f')
            ctrl_312 = 0

    def exe_freq_156(self):
        global ctrl_156
		
        if ctrl_156 == 0:
            ser.write(b'6')
            ctrl_156 = 1
        else:
            ser.write(b'v')
            ctrl_156 = 0

    def exe_som1(self):			#FUNCAO ACIONADA PELO BOTAO DO SOM PREDEFINIDO
        global pp_ctrl			#DECLARA QUE FUNCAO UTILIZA VARIAVEL GLOBAL
        ser.write(b'7')			#ENVIA VARIAVEL QUE ATIVA O SOM PREDEFINIDO
        pp_ctrl = 1				#ALTERA VARIAVEL DE CONTROLE
								#E O PROCESSO SE REPETE 4X
    def exe_som2(self):
        global pp_ctrl
        ser.write(b'8')
        pp_ctrl = 1

    def exe_som3(self):
        global pp_ctrl
        ser.write(b'9')
        pp_ctrl = 1

    def exe_som4(self):
        global pp_ctrl
        ser.write(b'0')
        pp_ctrl = 1

    def exe_prog(self):			#FUNCAO ACIONADA PELO BOTAO DE PROGRAMACAO
        global pp_ctrl	
        ser.write(b'p')			#ENVIA SINAL PARA ATIVAR A CONFIGURACAO
        pp_ctrl = 0				#ALTERA VARIAVEL DE CONTROLE DE PLAY/PAUSE

    def exe_play_pause(self):	#FUNCAO QUE EH ATIVADA PELO BOTAO PLAY/PAUSE E ENVIA SINAL DE CONTROLE
        global pp_ctrl			#DECLARA QUE FUNCAO UTILIZA VARIAVEL GLOBAL
        if pp_ctrl == 1:		#SE BOTAO APERTADO E PLAY/PAUSE ESTA EM PLAY
            ser.write(b'o')		#ENVIA SINAL PARA PARAR DE TOCAR SINAL PREDEFINIDO OU GRAVADO
            pp_ctrl = 0			#ALTERA VARIAVEL DE CONTROLE
        elif pp_ctrl == 0:		#SE BOTAO APERTADO E PLAY/PAUSE ESTA EM PAUSE
            ser.write(b'i')		#ALTERA VARIAVEL DE CONTROLE
            pp_ctrl = 1			#ENVIA SINAL PARA DAR PLAY DE NO SINAL GRAVADO

#MAIN DA INTERFACE
if __name__ == "__main__":
    application = QtWidgets.QApplication(sys.argv)          #instancia da clase QApplication
    window=QtWidgets.QMainWindow()
    main_window = Ui_Form()
    main_window.setupUi(window)
    window.show()
    sys.exit(application.exec_())                           #loop para mostrar a janela e fechar corretamente