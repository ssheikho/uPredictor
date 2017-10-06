from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys

class Create_numbers(QWidget):
    def __init__(self):
        super().__init__()
        self.combi = combi()

        self.number_grid = QGridLayout()

        self.lcd0 = QLCDNumber()
        self.lcd1 = QLCDNumber()
        self.lcd2 = QLCDNumber()
        self.lcd3 = QLCDNumber()

        self.number_grid.addWidget(self.lcd0, 0, 0)
        self.number_grid.addWidget(self.lcd1, 0, 1)
        self.number_grid.addWidget(self.lcd2, 0, 2)
        self.number_grid.addWidget(self.lcd3, 0, 3)

        self.setLayout(self.number_grid)


    def methods(self,i):

        self.numbers2show = self.combi[i]

        self.lcd0.display(self.numbers2show[0])
        self.lcd1.display(self.numbers2show[1])
        self.lcd2.display(self.numbers2show[2])
        self.lcd3.display(self.numbers2show[3])




def combi():
    p = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23]

    N = random.sample(p,24)

    # DEFINING TUPLES
    p[0] = (1, 2, 3, 4)
    p[1] = (1, 2, 4, 3)
    p[2] = (1, 3, 2, 4)
    p[3] = (1, 3, 4, 2)
    p[4] = (1, 4, 2, 3)
    p[5] = (1, 4, 3, 2)

    p[6] = (2, 1, 3, 4)
    p[7] = (2, 1, 4, 3)
    p[8] = (2, 3, 1, 4)
    p[9] = (2, 3, 4, 1)
    p[10] = (2, 4, 1, 3)
    p[11] = (2, 4, 3, 1)

    p[12] = (3, 1, 2, 4)
    p[13] = (3, 1, 4, 2)
    p[14] = (3, 2, 1, 4)
    p[15] = (3, 2, 4, 1)
    p[16] = (3, 4, 1, 2)
    p[17] = (3, 4, 2, 1)

    p[18] = (4, 1, 2, 3)
    p[19] = (4, 1, 3, 2)
    p[20] = (4, 2, 1, 3)
    p[21] = (4, 2, 3, 1)
    p[22] = (4, 3, 2, 1)
    p[23] = (4, 3, 1, 2)

    Set_tuple_list = []

    for x in N:
        Set_tuple_list.append(p[x])

    return Set_tuple_list


