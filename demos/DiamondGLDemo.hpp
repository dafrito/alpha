#ifndef DIAMONDGLDEMO_H
#define DIAMONDGLDEMO_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>

class DiamondGLWidget;

class DiamondGLDemo : public QWidget
{
	Q_OBJECT
	
	DiamondGLWidget* const glWidget;

	QCheckBox* const useDepthTestingOption;
	QCheckBox* const useBackFaceCullingOption;
	QCheckBox* const drawBacksAsWireframeOption;
	QCheckBox* const correctWindingOrderOption;

	QLabel* const descriptionLabel;
private slots:
	void setUseBackFaceCulling(const bool backFaceCulling);
	void setUseDepthTesting(const bool useDepthTesting);
	void setCorrectWindingOrder(const bool correctWindingOrder);
	void setDrawBacksAsWireframe(const bool drawBacksAsWireframe);

	void updateDescription();
public:
	DiamondGLDemo(QWidget* const parent = 0);

};

#endif // DIAMONDGLDEMO_H
