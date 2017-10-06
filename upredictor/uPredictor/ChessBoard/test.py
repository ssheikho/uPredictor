import numpy as np
import cv2
import glob
 
# termination criteria
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

# checkerboard Dimensions
cbrow = 4
cbcol = 4

# prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
objp = np.zeros((cbrow * cbcol, 3), np.float32)
objp[:, :2] = np.mgrid[0:cbcol, 0:cbrow].T.reshape(-1, 2)

# Arrays to store object points and image points from all the images.
objpoints = [] # 3d point in real world space
imgpoints = [] # 2d points in image plane.
images = glob.glob('*.jpg')

print images

for fname in images:
	print fname
	img = cv2.imread(fname)
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	# Find the chess board corners
	cv2.imshow('orig img', gray)
	cv2.waitKey(500)
	ret, corners = cv2.findChessboardCorners(gray, (cbrow, cbcol), None)
	# If found, add object points, image points (after refining them)
	if ret == True:
		objpoints.append(objp)
		cv2.cornerSubPix(gray, corners, (5,5), (-1,-1), criteria)
		imgpoints.append(zip(*corners))
		# Draw and display the corners
		cv2.drawChessboardCorners(img, (cbrow, cbcol), corners, ret)
		cv2.imshow('img', img)
		cv2.waitKey(500)

cv2.destroyAllWindows()

gray = np.array(gray)

objpoints = np.array(objpoints, 'float32')
imgpoints = np.array(imgpoints[0], 'float32')

print len(objpoints[0])
print len(imgpoints[0])

ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)

img = cv2.imread('cb.png')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
img = gray
h,  w = img.shape[:2]
newcameramtx, roi = cv2.getOptimalNewCameraMatrix(mtx, dist, (w,h), 1, (w,h))

# undistort
dst = cv2.undistort(img, mtx, dist, None, newcameramtx)

# crop the image
x, y, w, h = roi
dst = dst[y:y+h, x:x+w]
print dst
cv2.imwrite('calibresult.png', dst)

mean_error = 0
for i in xrange(len(objpoints)):
	imgpoints2, _ = cv2.projectPoints(objpoints[i], rvecs[i], tvecs[i], mtx, dist)
	imgpoints2 = np.array(zip(*imgpoints2))
	imgpoints2 = imgpoints2[0]
	error = cv2.norm(imgpoints[i], imgpoints2, cv2.NORM_L2)/len(imgpoints2)
	mean_error += error

print "total error: ", mean_error/len(objpoints)
