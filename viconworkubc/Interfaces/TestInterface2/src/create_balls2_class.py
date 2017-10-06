from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys


class Create_balls(QWidget):
    def __init__(self):
        super().__init__()
        self.combi1 = combi()
        self.combi2 = combi()

        self.combi_letters = combi_letters()

    def first_layout(self):

        self.frame_number_grid = QFrame()

        self.frame_number_grid.setFrameStyle(QFrame.Box | QFrame.Raised)
        self.frame_number_grid.setLineWidth(2)
        self.frame_number_grid.setMidLineWidth(3)
        self.frame_number_grid.setMinimumSize(690, 650)

        self.number_grid = QHBoxLayout()
        self.number_grid.setAlignment(Qt.AlignCenter)

        self.lcd0 = QLabel()
        self.lcd1 = QLabel()
        self.lcd2 = QLabel()
        self.lcd3 = QLabel()

        self.number_grid.addWidget(self.lcd0)
        self.number_grid.addWidget(self.lcd1)
        self.number_grid.addWidget(self.lcd2)
        self.number_grid.addWidget(self.lcd3)

        self.numbox = QHBoxLayout()
        self.numbox.setAlignment(Qt.AlignCenter)

        self.numbox0 = QLabel()
        self.numbox1 = QLabel()
        self.numbox2 = QLabel()
        self.numbox3 = QLabel()

        self.numbox.addWidget(self.numbox0)
        self.numbox.addWidget(self.numbox1)
        self.numbox.addWidget(self.numbox2)
        self.numbox.addWidget(self.numbox3)

        self.racksnumbers = []

        self.racksnumbers.append(QPixmap(":/1.png"))
        self.racksnumbers.append(QPixmap(":/2.png"))
        self.racksnumbers.append(QPixmap(":/3.png"))
        self.racksnumbers.append(QPixmap(":/4.png"))

        self.numbox0.setPixmap(self.racksnumbers[0])
        self.numbox1.setPixmap(self.racksnumbers[1])
        self.numbox2.setPixmap(self.racksnumbers[2])
        self.numbox3.setPixmap(self.racksnumbers[3])

        self.tab1 = QVBoxLayout()
        self.tab1.setAlignment(Qt.AlignCenter)
        self.tab1.addLayout(self.number_grid)
        self.tab1.addLayout(self.numbox)

        self.frame_number_grid.setLayout(self.tab1)

        return self.frame_number_grid

    def second_layout1(self):

        self.rack = QHBoxLayout()
        self.rack.setAlignment(Qt.AlignCenter)

        self.rack0 = QLabel()
        self.rack1 = QLabel()
        self.rack2 = QLabel()
        self.rack3 = QLabel()

        self.rack.addWidget(self.rack0)
        self.rack.addWidget(self.rack1)
        self.rack.addWidget(self.rack2)
        self.rack.addWidget(self.rack3)

        self.frame_rack = QFrame()

        self.frame_rack.setFrameStyle(QFrame.Box | QFrame.Raised)
        self.frame_rack.setLineWidth(2)
        self.frame_rack.setMidLineWidth(3)
        self.frame_rack.setMinimumSize(650, 150)

        self.frame_rack.setLayout(self.rack)

        return self.frame_rack

    def second_layout2(self):

        self.basket1 = QHBoxLayout()
        self.basket1.setAlignment(Qt.AlignCenter)

        self.basket2 = QHBoxLayout()
        self.basket2.setAlignment(Qt.AlignCenter)

        self.one = QLabel()
        self.two = QLabel()
        self.three = QLabel()
        self.four = QLabel()

        self.basket1.addWidget(self.one)
        self.basket1.addWidget(self.two)
        self.basket2.addWidget(self.three)
        self.basket2.addWidget(self.four)

        self.basket = QVBoxLayout()
        self.basket.addLayout(self.basket1)
        self.basket.addLayout(self.basket2)

        self.frame_basket = QFrame()

        self.frame_basket.setFrameStyle(QFrame.Box | QFrame.Raised)
        self.frame_basket.setLineWidth(2)
        self.frame_basket.setMidLineWidth(3)
        self.frame_basket.setMinimumSize(650, 640)

        self.frame_basket.setLayout(self.basket)

        return self.frame_basket

    def letters_method(self, i):
        Llist = self.combi_letters[i]
        self.letters = []

        for currPlot in Llist:
            self.letters.append(QPixmap(":/" + currPlot + ".png"))

        pos_0 = self.letters[0]
        pos_1 = self.letters[1]
        pos_2 = self.letters[2]
        pos_3 = self.letters[3]  #.scaled(128, 128, Qt.KeepAspectRatio)

        self.lcd0.setPixmap(pos_0)
        self.lcd1.setPixmap(pos_1)
        self.lcd2.setPixmap(pos_2)
        self.lcd3.setPixmap(pos_3)

        self.number_balls = plot(Llist)
        return Llist

    def numbers_method(self,i):

        rack_list = random.sample(self.combi1[i],4)
        basket_list = random.sample(self.combi2[i],4)

        self.pos = []

        for currPlot in self.number_balls:
            self.pos.append(QPixmap(":/" + currPlot + ".png"))

        self.one.setPixmap(self.pos[basket_list[0]-1])
        self.two.setPixmap(self.pos[basket_list[1]-1])
        self.three.setPixmap(self.pos[basket_list[2]-1])
        self.four.setPixmap(self.pos[basket_list[3]-1])

        self.rack0.setPixmap(self.pos[rack_list[0]-1].scaled(128, 128, Qt.KeepAspectRatio))
        self.rack1.setPixmap(self.pos[rack_list[1]-1].scaled(128, 128, Qt.KeepAspectRatio))
        self.rack2.setPixmap(self.pos[rack_list[2]-1].scaled(128, 128, Qt.KeepAspectRatio))
        self.rack3.setPixmap(self.pos[rack_list[3]-1].scaled(128, 128, Qt.KeepAspectRatio))

        return [basket_list, rack_list]


def plot(Llist):
    item = 0
    for x in Llist:
        if x == 'A':
            if item == 0:
                pos1 = '1Y'
            elif item == 1:
                pos2 = '2Y'
            elif item == 2:
                pos3 = '3Y'
            else:
                pos4 = '4Y'
        elif x == 'B':
            if item == 0:
                pos1 = '1B'
            elif item == 1:
                pos2 = '2B'
            elif item == 2:
                pos3 = '3B'
            else:
                pos4 = '4B'
        elif x == 'C':
            if item == 0:
                pos1 = '1R'
            elif item == 1:
                pos2 = '2R'
            elif item == 2:
                pos3 = '3R'
            else:
                pos4 = '4R'
        elif x == 'D':
            if item == 0:
                pos1 = '1G'
            elif item == 1:
                pos2 = '2G'
            elif item == 2:
                pos3 = '3G'
            else:
                pos4 = '4G'
        item = item + 1
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


def combi_letters():
    p = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23]

    N = random.sample(p, 24)

    p[0] = ['A', 'B', 'C', 'D']
    p[1] = ['A', 'B', 'D', 'C']
    p[2] = ['A', 'C', 'B', 'D']
    p[3] = ['A', 'C', 'D', 'B']
    p[4] = ['A', 'D', 'B', 'C']
    p[5] = ['A', 'D', 'C', 'B']

    p[6] = ['B', 'A', 'C', 'D']
    p[7] = ['B', 'A', 'D', 'C']
    p[8] = ['B', 'C', 'A', 'D']
    p[9] = ['B', 'C', 'D', 'A']
    p[10] = ['B', 'D', 'A', 'C']
    p[11] = ['B', 'D', 'C', 'A']

    p[12] = ['C', 'A', 'B', 'D']
    p[13] = ['C', 'A', 'D', 'B']
    p[14] = ['C', 'B', 'A', 'D']
    p[15] = ['C', 'B', 'D', 'A']
    p[16] = ['C', 'D', 'A', 'B']
    p[17] = ['C', 'D', 'B', 'A']

    p[18] = ['D', 'A', 'B', 'C']
    p[19] = ['D', 'A', 'C', 'B']
    p[20] = ['D', 'B', 'A', 'C']
    p[21] = ['D', 'B', 'C', 'A']
    p[22] = ['D', 'C', 'B', 'A']
    p[23] = ['D', 'C', 'A', 'B']

    Set_image_list = []

    for x in N:
        Set_image_list.append(p[x])

    return Set_image_list