from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys
import resources2
from create_numbers2_class import *

class Create_pictures(QGraphicsView):
    def __init__(self):
        super().__init__()

        self.number_grid = QGridLayout()

        self.combi = combi()

        self.one = QLabel()
        self.two = QLabel()
        self.three = QLabel()
        self.four = QLabel()

        self.number_grid.addWidget(self.one, 0, 0)
        self.number_grid.addWidget(self.two, 0, 1)
        self.number_grid.addWidget(self.three, 1, 0)
        self.number_grid.addWidget(self.four, 1, 1)

        self.setLayout(self.number_grid)

    def methods2(self,i):

        list = self.combi[i]

        self.pos = plot(list)

        self.one.setPixmap(self.pos[0])
        self.two.setPixmap(self.pos[1])
        self.three.setPixmap(self.pos[2])
        self.four.setPixmap(self.pos[3])

def plot(list):
    item=0
    for x in list:
        if x == 1:
            if item == 0:
                pos1 = QPixmap(":/uno.png")
            elif item == 1:
                pos2 = QPixmap(":/uno.png")
            elif item == 2:
                pos3 = QPixmap(":/uno.png")
            else:
                pos4 = QPixmap(":/uno.png")
                # return item
        elif x == 2:
            if item == 0:
                pos1 = QPixmap(":/dos.png")
            elif item == 1:
                pos2 = QPixmap(":/dos.png")
            elif item == 2:
                pos3 = QPixmap(":/dos.png")
            else:
                pos4 = QPixmap(":/dos.png")
                # return item
        elif x == 3:
            if item == 0:
                pos1 = QPixmap(":/tres.png")
            elif item == 1:
                pos2 = QPixmap(":/tres.png")
            elif item == 2:
                pos3 = QPixmap(":/tres.png")
            else:
                pos4 = QPixmap(":/tres.png")
                # return item
        elif x == 4:
            if item == 0:
                pos1 = QPixmap(":/cuatro.png")
            elif item == 1:
                pos2 = QPixmap(":/cuatro.png")
            elif item == 2:
                pos3 = QPixmap(":/cuatro.png")
            else:
                pos4 = QPixmap(":/cuatro.png")
                # return item
        item=item+1
    return [pos1, pos2, pos3, pos4]

def combi():
    p = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23]

    N = random.sample(p, 24)

    p[0] = [1, 2, 3, 4]
    p[1] = [1, 2, 4, 3]
    p[2] = [1, 3, 2, 4]
    p[3] = [1, 3, 4, 2]
    p[4] = [1, 4, 2, 3]
    p[5] = [1, 4, 3, 2]

    p[6] = [2, 1, 3, 4]
    p[7] = [2, 1, 4, 3]
    p[8] = [2, 3, 1, 4]
    p[9] = [2, 3, 4, 1]
    p[10] = [2, 4, 1, 3]
    p[11] = [2, 4, 3, 1]

    p[12] = [3, 1, 2, 4]
    p[13] = [3, 1, 4, 2]
    p[14] = [3, 2, 1, 4]
    p[15] = [3, 2, 4, 1]
    p[16] = [3, 4, 1, 2]
    p[17] = [3, 4, 2, 1]

    p[18] = [4, 1, 2, 3]
    p[19] = [4, 1, 3, 2]
    p[20] = [4, 2, 1, 3]
    p[21] = [4, 2, 3, 1]
    p[22] = [4, 3, 2, 1]
    p[23] = [4, 3, 1, 2]

    Set_image_list = []

    for x in N:
        Set_image_list.append(p[x])

    return Set_image_list