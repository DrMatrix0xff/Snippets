#!/usr/bin/env python
# coding: utf8

import sys
import time
import random
from PyQt4 import QtGui
from PyQt4 import QtCore

Bean = u''
Is_bean_set = QtCore.QWaitCondition()
Lock = QtCore.QMutex()

class Worker(QtCore.QObject):
    finished = QtCore.pyqtSignal()
    logmsg = QtCore.pyqtSignal(unicode)

    @QtCore.pyqtSlot()
    def do_work(self):
        global Bean
        midi = random.randint(1, 100)
        stop = False
        Lock.lock()
        while not stop:
            while 1:
                Is_bean_set.wait(Lock)
                self.logmsg.emit(u'You have input: ' + Bean)
                if Bean.isdigit():
                    break
                else:
                    self.logmsg.emit(u'请输入数字!')
            guess = int(Bean)
            if midi > guess:
                self.logmsg.emit(u'guess too small...')
            elif midi < guess:
                self.logmsg.emit(u'guess too big...')
            else:
                self.logmsg.emit(u'great, you have made it!')
                stop = True
        Lock.unlock()
        self.finished.emit()


class Example(QtGui.QMainWindow):

    def __init__(self):
        super(Example, self).__init__() 

        self.worker = Worker()
        self.dispatch_thread = QtCore.QThread()
        self.worker.moveToThread(self.dispatch_thread)
        self.worker.finished.connect(self.dispatch_thread.quit)
        self.dispatch_thread.started.connect(self.worker.do_work)

        self.initUI()

    def initUI(self):

        self.le1 = QtGui.QLineEdit(self)
        self.le1.move(30, 50)

        btn2 = QtGui.QPushButton("Bang!", self)
        btn2.move(150, 50)

        self.le1.returnPressed.connect(self.passNumber)
        btn2.clicked.connect(self.accumulateClicked)

        screen = QtGui.QPlainTextEdit(self)
        screen.setReadOnly(True)
        screen.setGeometry(30, 90, 360, 270)
        screen.appendPlainText(u'请点击按钮，开始猜数字游戏, 数字范围1~100')
        self.worker.logmsg.connect(screen.appendPlainText)

        self.setGeometry(300, 300, 500, 375)
        self.setWindowTitle('Accumulator')
        self.show()

    def passNumber(self):
        global Bean
        Lock.lock()
        Bean = unicode(self.le1.text())
        Is_bean_set.wakeOne()
        Lock.unlock()

    def accumulateClicked(self):
        self.dispatch_thread.start()

def main():

    app = QtGui.QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
