#!/usr/bin/env python
# coding: utf-8

import sys
import array
from PyQt4 import QtGui
from PyQt4 import QtCore

DataSize = 12000
BufferSize = 8192

buff = array.array('c', [' '] * BufferSize)

freeBytes = QtCore.QSemaphore(BufferSize)
usedBytes = QtCore.QSemaphore()

class Producer(QtCore.QObject):
    finished = QtCore.pyqtSignal()

    def produce(self):
        QtCore.qsrand(QtCore.QTime(0,0,0).secsTo(QtCore.QTime.currentTime()))
        i = 0
        while i < DataSize:
            freeBytes.acquire()
            buff[i % BufferSize] = chr(97 + QtCore.qrand() % 26)
            usedBytes.release()
            i += 1
        self.finished.emit()

class Consumer(QtCore.QObject):
    finished = QtCore.pyqtSignal()
    CharConsumed = QtCore.pyqtSignal(str)

    def consume(self):
        i = 0
        while i < DataSize:
            usedBytes.acquire()
            self.CharConsumed.emit(buff[i % BufferSize])
            freeBytes.release()
            i += 1
        self.CharConsumed.emit("consumer thread consume over")
        self.finished.emit()

class MainApp(QtGui.QMainWindow):

    def __init__(self):
        super(MainApp, self).__init__()
        self.producer = Producer()
        self.consumer = Consumer()
        self.p_thread = QtCore.QThread()
        self.c_thread = QtCore.QThread()
        self.producer.moveToThread(self.p_thread)
        self.consumer.moveToThread(self.c_thread)

        self.p_thread.started.connect(self.producer.produce)
        self.c_thread.started.connect(self.consumer.consume)
        self.consumer.CharConsumed.connect(self.output_screen)

        self.consumer.finished.connect(self.c_thread.quit)
        self.producer.finished.connect(self.p_thread.quit)

        self.InitUserInterface()

    def InitUserInterface(self):
        btn = QtGui.QPushButton("Bang!", self)
        btn.move(150, 50)
        btn.clicked.connect(self.start_threads)

        self.screen = QtGui.QPlainTextEdit(self)
        self.screen.setReadOnly(True)
        self.screen.setGeometry(150, 100, 400, 300)

        self.setGeometry(300, 300, 750, 450)
        self.setWindowTitle('Bang')
        self.show()

    def start_threads(self):
        self.c_thread.start()
        self.p_thread.start()

    @QtCore.pyqtSlot(str)
    def output_screen(self, s):
        self.screen.appendPlainText(s)

def main():
    app = QtGui.QApplication(sys.argv)
    xx = MainApp()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
