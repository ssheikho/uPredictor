#ifndef ANNOTATION_UI_FACTORY_H
#define ANNOTATION_UI_FACTORY_H

class AnnotationValue;
//class KinectPlayer;
class LayoutContainer;
class LayoutElement;

class AnnotationUIFactory {
public:
	AnnotationUIFactory();//KinectPlayer &kp);
	~AnnotationUIFactory();

	LayoutElement *createUI(AnnotationValue *av, LayoutContainer *parent);

protected:
	//KinectPlayer &_kp;
};

#endif