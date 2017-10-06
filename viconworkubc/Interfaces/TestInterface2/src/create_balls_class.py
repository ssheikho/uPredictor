from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import sys

class Create_balls(QWidget):
    def __init__(self):
        super().__init__()
        self.combi1 = combi()
        self.combi2 = combi()

    def first_layout(self):

        self.frame_number_grid = QFrame()

        self.frame_number_grid.setFrameStyle(QFrame.Box | QFrame.Raised)
        self.frame_number_grid.setLineWidth(2)
        self.frame_number_grid.setMidLineWidth(3)

        self.frame_number_grid.setMinimumSize(650, 150)

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

        self.frame_number_grid.setLayout(self.number_grid)

        return  self.frame_number_grid

    def second_layout(self):

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

        self.gbox = QVBoxLayout()
        self.gbox.addLayout(self.basket1)
        self.gbox.addLayout(self.basket2)

        self.frame_gbox = QFrame()

        self.frame_gbox.setFrameStyle(QFrame.Box | QFrame.Raised)
        self.frame_gbox.setLineWidth(2)
        self.frame_gbox.setMidLineWidth(3)
        self.frame_gbox.setMinimumSize(650, 640)

        self.frame_gbox.setLayout(self.gbox)

        return self.frame_gbox

    def methods(self,i):

        nlist = self.combi1[i]
        clist = self.combi2[i]

        self.pos = []
        generatedNumColors = plot(nlist,clist)
        for currPlot in generatedNumColors:
            self.pos.append(QPixmap(":/" + currPlot + ".png"))

        pos_0 = self.pos[0].scaled(128, 128, Qt.KeepAspectRatio)
        pos_1 = self.pos[1].scaled(128, 128, Qt.KeepAspectRatio)
        pos_2 = self.pos[2].scaled(128, 128, Qt.KeepAspectRatio)
        pos_3 = self.pos[3].scaled(128, 128, Qt.KeepAspectRatio)

        self.lcd0.setPixmap(pos_0)
        self.lcd1.setPixmap(pos_1)
        self.lcd2.setPixmap(pos_2)
        self.lcd3.setPixmap(pos_3)

        return generatedNumColors

    def methods2(self):

        n = [0,1,2,3]

        N = random.sample(n,4)

        self.one.setPixmap(self.pos[N[0]])
        self.two.setPixmap(self.pos[N[1]])
        self.three.setPixmap(self.pos[N[2]])
        self.four.setPixmap(self.pos[N[3]])

        return N

# def plot(nlist,clist):
#     item=0
#     for x in nlist:
#         if x == 1:
#             if item == 0:
#                 if clist[item] == 1: # 1B
#                     pos1 = QPixmap(":/1B.png")
#                 elif clist[item] == 2: #1G
#                     pos1 = QPixmap(":/1G.png")
#                 elif clist[item] == 3: #1Y
#                     pos1 = QPixmap(":/1Y.png")
#                 else:   #1R
#                     pos1 = QPixmap(":/1R.png")
#             elif item == 1:
#                 if clist[item] == 1: # 1B
#                     pos2 = QPixmap(":/1B.png")
#                 elif clist[item] == 2: #1G
#                     pos2 = QPixmap(":/1G.png")
#                 elif clist[item] == 3: #1Y
#                     pos2 = QPixmap(":/1Y.png")
#                 else:   #1R
#                     pos2 = QPixmap(":/1R.png")
#             elif item == 2:
#                 if clist[item] == 1: # 1B
#                     pos3 = QPixmap(":/1B.png")
#                 elif clist[item] == 2: #1G
#                     pos3 = QPixmap(":/1G.png")
#                 elif clist[item] == 3: #1Y
#                     pos3 = QPixmap(":/1Y.png")
#                 else:   #1R
#                     pos3 = QPixmap(":/1R.png")
#             else:
#                 if clist[item] == 1: # 1B
#                     pos4 = QPixmap(":/1B.png")
#                 elif clist[item] == 2: #1G
#                     pos4 = QPixmap(":/1G.png")
#                 elif clist[item] == 3: #1Y
#                     pos4 = QPixmap(":/1Y.png")
#                 else:   #1R
#                     pos4 = QPixmap(":/1R.png")
#                 # return item
#         elif x == 2:
#             if item == 0:
#                 if clist[item]==1: # 2B
#                     pos1 = QPixmap(":/2B.png")
#                 elif clist[item]==2: #2G
#                     pos1 = QPixmap(":/2G.png")
#                 elif clist[item]==3: #2Y
#                     pos1 = QPixmap(":/2Y.png")
#                 else:   #2R
#                     pos1 = QPixmap(":/2R.png")
#             elif item == 1:
#                 if clist[item]==1: # 2B
#                     pos2 = QPixmap(":/2B.png")
#                 elif clist[item]==2: #2G
#                     pos2 = QPixmap(":/2G.png")
#                 elif clist[item]==3: #2Y
#                     pos2 = QPixmap(":/2Y.png")
#                 else:   #2R
#                     pos2 = QPixmap(":/2R.png")
#             elif item == 2:
#                 if clist[item]==1: # 2B
#                     pos3 = QPixmap(":/2B.png")
#                 elif clist[item]==2: #2G
#                     pos3 = QPixmap(":/2G.png")
#                 elif clist[item]==3: #2Y
#                     pos3 = QPixmap(":/2Y.png")
#                 else:   #2R
#                     pos3 = QPixmap(":/2R.png")
#             else:
#                 if clist[item]==1: # 2B
#                     pos4 = QPixmap(":/2B.png")
#                 elif clist[item]==2: #2G
#                     pos4 = QPixmap(":/2G.png")
#                 elif clist[item]==3: #2Y
#                     pos4 = QPixmap(":/2Y.png")
#                 else:   #2R
#                     pos4 = QPixmap(":/2R.png")
#                 # return item
#         elif x == 3:
#             if item == 0:
#                 if clist[item]==1: # 3B
#                     pos1 = QPixmap(":/3B.png")
#                 elif clist[item]==2: #3G
#                     pos1 = QPixmap(":/3G.png")
#                 elif clist[item]==3: #3Y
#                     pos1 = QPixmap(":/3Y.png")
#                 else:   #3R
#                     pos1 = QPixmap(":/3R.png")
#             elif item == 1:
#                 if clist[item]==1: # 3B
#                     pos2 = QPixmap(":/3B.png")
#                 elif clist[item]==2: #3G
#                     pos2 = QPixmap(":/3G.png")
#                 elif clist[item]==3: #3Y
#                     pos2 = QPixmap(":/3Y.png")
#                 else:   #3R
#                     pos2 = QPixmap(":/3R.png")
#             elif item == 2:
#                 if clist[item]==1: # 3B
#                     pos3 = QPixmap(":/3B.png")
#                 elif clist[item]==2: #3G
#                     pos3 = QPixmap(":/3G.png")
#                 elif clist[item]==3: #3Y
#                     pos3 = QPixmap(":/3Y.png")
#                 else:   #3R
#                     pos3 = QPixmap(":/3R.png")
#             else:
#                 if clist[item]==1: # 3B
#                     pos4 = QPixmap(":/3B.png")
#                 elif clist[item]==2: #3G
#                     pos4 = QPixmap(":/3G.png")
#                 elif clist[item]==3: #3Y
#                     pos4 = QPixmap(":/3Y.png")
#                 else:   #3R
#                     pos4 = QPixmap(":/3R.png")
#                 # return item
#         elif x == 4:
#             if item == 0:
#                 if clist[item]==1: # 4B
#                     pos1 = QPixmap(":/4B.png")
#                 elif clist[item]==2: # 4G
#                     pos1 = QPixmap(":/4G.png")
#                 elif clist[item]==3: # 4Y
#                     pos1 = QPixmap(":/4Y.png")
#                 else:   # 4R
#                     pos1 = QPixmap(":/4R.png")
#             elif item == 1:
#                 if clist[item]==1: # 4B
#                     pos2 = QPixmap(":/4B.png")
#                 elif clist[item]==2: # 4G
#                     pos2 = QPixmap(":/4G.png")
#                 elif clist[item]==3: # 4Y
#                     pos2 = QPixmap(":/4Y.png")
#                 else:   # 4R
#                     pos2 = QPixmap(":/4R.png")
#             elif item == 2:
#                 if clist[item]==1: # 4B
#                     pos3 = QPixmap(":/4B.png")
#                 elif clist[item]==2: # 4G
#                     pos3 = QPixmap(":/4G.png")
#                 elif clist[item]==3: # 4Y
#                     pos3 = QPixmap(":/4Y.png")
#                 else:   # 4R
#                     pos3 = QPixmap(":/4R.png")
#             else:
#                 if clist[item]==1: # 4B
#                     pos4 = QPixmap(":/4B.png")
#                 elif clist[item]==2: # 4G
#                     pos4 = QPixmap(":/4G.png")
#                 elif clist[item]==3: # 4Y
#                     pos4 = QPixmap(":/4Y.png")
#                 else:   # 4R
#                     pos4 = QPixmap(":/4R.png")
#                 # return item
#         item=item+1
#     return [pos1, pos2, pos3, pos4]


def plot(nlist,clist):
    item=0
    for x in nlist:
        if x == 1:
            if item == 0:
                if clist[item] == 1: # 1B
                    pos1 = '1B'
                elif clist[item] == 2: #1G
                    pos1 = '1G'
                elif clist[item] == 3: #1Y
                    pos1 = '1Y'
                else:   #1R
                    pos1 = '1R'
            elif item == 1:
                if clist[item] == 1: # 1B
                    pos2 = '1B'
                elif clist[item] == 2: #1G
                    pos2 = '1G'
                elif clist[item] == 3: #1Y
                    pos2 = '1Y'
                else:   #1R
                    pos2 = '1R'
            elif item == 2:
                if clist[item] == 1: # 1B
                    pos3 = '1B'
                elif clist[item] == 2: #1G
                    pos3 = '1G'
                elif clist[item] == 3: #1Y
                    pos3 = '1Y'
                else:   #1R
                    pos3 = '1R'
            else:
                if clist[item] == 1: # 1B
                    pos4 = '1B'
                elif clist[item] == 2: #1G
                    pos4 = '1G'
                elif clist[item] == 3: #1Y
                    pos4 = '1Y'
                else:   #1R
                    pos4 = '1R'
                # return item
        elif x == 2:
            if item == 0:
                if clist[item]==1: # 2B
                    pos1 = '2B'
                elif clist[item]==2: #2G
                    pos1 = '2G'
                elif clist[item]==3: #2Y
                    pos1 = '2Y'
                else:   #2R
                    pos1 = '2R'
            elif item == 1:
                if clist[item]==1: # 2B
                    pos2 = '2B'
                elif clist[item]==2: #2G
                    pos2 = '2G'
                elif clist[item]==3: #2Y
                    pos2 = '2Y'
                else:   #2R
                    pos2 = '2R'
            elif item == 2:
                if clist[item]==1: # 2B
                    pos3 = '2B'
                elif clist[item]==2: #2G
                    pos3 = '2G'
                elif clist[item]==3: #2Y
                    pos3 = '2Y'
                else:   #2R
                    pos3 = '2R'
            else:
                if clist[item]==1: # 2B
                    pos4 = '2B'
                elif clist[item]==2: #2G
                    pos4 = '2G'
                elif clist[item]==3: #2Y
                    pos4 = '2Y'
                else:   #2R
                    pos4 = '2R'
                # return item
        elif x == 3:
            if item == 0:
                if clist[item]==1: # 3B
                    pos1 = '3B'
                elif clist[item]==2: #3G
                    pos1 = '3G'
                elif clist[item]==3: #3Y
                    pos1 = '3Y'
                else:   #3R
                    pos1 = '3R'
            elif item == 1:
                if clist[item]==1: # 3B
                    pos2 = '3B'
                elif clist[item]==2: #3G
                    pos2 = '3G'
                elif clist[item]==3: #3Y
                    pos2 = '3Y'
                else:   #3R
                    pos2 = '3R'
            elif item == 2:
                if clist[item]==1: # 3B
                    pos3 = '3B'
                elif clist[item]==2: #3G
                    pos3 = '3G'
                elif clist[item]==3: #3Y
                    pos3 = '3Y'
                else:   #3R
                    pos3 = '3R'
            else:
                if clist[item]==1: # 3B
                    pos4 = '3B'
                elif clist[item]==2: #3G
                    pos4 = '3G'
                elif clist[item]==3: #3Y
                    pos4 = '3Y'
                else:   #3R
                    pos4 = '3R'
                # return item
        elif x == 4:
            if item == 0:
                if clist[item]==1: # 4B
                    pos1 = '4B'
                elif clist[item]==2: # 4G
                    pos1 = '4G'
                elif clist[item]==3: # 4Y
                    pos1 = '4Y'
                else:   # 4R
                    pos1 = '4R'
            elif item == 1:
                if clist[item]==1: # 4B
                    pos2 = '4B'
                elif clist[item]==2: # 4G
                    pos2 = '4G'
                elif clist[item]==3: # 4Y
                    pos2 = '4Y'
                else:   # 4R
                    pos2 = '4R'
            elif item == 2:
                if clist[item]==1: # 4B
                    pos3 = '4B'
                elif clist[item]==2: # 4G
                    pos3 = '4G'
                elif clist[item]==3: # 4Y
                    pos3 = '4Y'
                else:   # 4R
                    pos3 = '4R'
            else:
                if clist[item]==1: # 4B
                    pos4 = '4B'
                elif clist[item]==2: # 4G
                    pos4 = '4G'
                elif clist[item]==3: # 4Y
                    pos4 = '4Y'
                else:   # 4R
                    pos4 = '4R'
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