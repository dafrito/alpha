#include <QtGui>
#include <cassert>

#include "DiamondGLWidget.h"
#include "DiamondGLDemo.h"

DiamondGLDemo::DiamondGLDemo(QWidget* const parent) :
	QWidget(parent),
	glWidget(new DiamondGLWidget(this)),
	useDepthTestingOption(new QCheckBox("Use Depth Testing")),
	useBackFaceCullingOption(new QCheckBox("Use Back-face Culling")),
	drawBacksAsWireframeOption(new QCheckBox("Draw Backs as Wireframe")),
	correctWindingOrderOption(new QCheckBox("Correct Winding Order")),
	descriptionLabel(new QLabel())
{
	QBoxLayout* const mainLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	setLayout(mainLayout);

	mainLayout->addWidget(glWidget, 1);

	QBoxLayout* const options = new QBoxLayout(QBoxLayout::TopToBottom);
	mainLayout->addLayout(options);

	useBackFaceCullingOption->setChecked(true);
	useBackFaceCullingOption->setToolTip("Sets whether back-facing polygons are drawn.");
	connect(useBackFaceCullingOption, SIGNAL(toggled(bool)), this, SLOT(setUseBackFaceCulling(bool)));
	connect(useBackFaceCullingOption, SIGNAL(toggled(bool)), this, SLOT(updateDescription()));
	options->addWidget(useBackFaceCullingOption);

	drawBacksAsWireframeOption->setEnabled(false);
	drawBacksAsWireframeOption->setChecked(true);
	drawBacksAsWireframeOption->setToolTip("Back-facing polygons will be drawn as wireframes.");
	connect(drawBacksAsWireframeOption, SIGNAL(toggled(bool)), this, SLOT(setDrawBacksAsWireframe(bool)));
	connect(drawBacksAsWireframeOption, SIGNAL(toggled(bool)), this, SLOT(updateDescription()));
	options->addWidget(drawBacksAsWireframeOption);

	useDepthTestingOption->setChecked(true);
	useDepthTestingOption->setToolTip("Ensure closer pixels always overwrite pixels that are further away.");
	connect(useDepthTestingOption, SIGNAL(toggled(bool)), this, SLOT(setUseDepthTesting(bool)));
	connect(useDepthTestingOption, SIGNAL(toggled(bool)), this, SLOT(updateDescription()));
	options->addWidget(useDepthTestingOption);

	correctWindingOrderOption->setChecked(true);
	correctWindingOrderOption->setToolTip("Correct the top of the diamond's winding so it renders properly.");
	connect(correctWindingOrderOption, SIGNAL(toggled(bool)), this, SLOT(setCorrectWindingOrder(bool)));
	connect(correctWindingOrderOption, SIGNAL(toggled(bool)), this, SLOT(updateDescription()));
	options->addWidget(correctWindingOrderOption);

	descriptionLabel->setWordWrap(true);
	descriptionLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);

	QScrollArea* const descriptionScrollPanel = new QScrollArea;
	descriptionScrollPanel->setWidget(descriptionLabel);
	descriptionScrollPanel->setFixedWidth(300);
	descriptionScrollPanel->setWidgetResizable(true);
	options->addWidget(descriptionScrollPanel);

	updateDescription();
}

void DiamondGLDemo::setUseDepthTesting(const bool useDepthTesting)
{
	glWidget->setUseDepthTesting(useDepthTesting);
	drawBacksAsWireframeOption->setEnabled(
		!glWidget->usingDepthTesting() && !glWidget->usingBackFaceCulling());
	correctWindingOrderOption->setEnabled(glWidget->usingBackFaceCulling() || !glWidget->usingDepthTesting());
}

void DiamondGLDemo::setUseBackFaceCulling(const bool backFaceCulling)
{
	glWidget->setUseBackFaceCulling(backFaceCulling);
	drawBacksAsWireframeOption->setEnabled(
		!glWidget->usingDepthTesting() && !glWidget->usingBackFaceCulling());
	correctWindingOrderOption->setEnabled(glWidget->usingBackFaceCulling() || !glWidget->usingDepthTesting());
}

void DiamondGLDemo::setDrawBacksAsWireframe(const bool drawBacksAsWireframe)
{
	glWidget->setDrawBacksAsWireframe(drawBacksAsWireframe);
	correctWindingOrderOption->setEnabled(
		glWidget->usingBackFaceCulling() || glWidget->drawingBacksAsWireframes());
}

void DiamondGLDemo::setCorrectWindingOrder(const bool correctWindingOrder)
{
	glWidget->setCorrectWindingOrder(correctWindingOrder);
}

void DiamondGLDemo::updateDescription()
{
	QString text;
	if (glWidget->usingBackFaceCulling()) {
		text += "Polygons that are back-facing are being removed. The winding order of ";
		text += "vertices is used to determine whether a polygon is front- or back-facing. ";
		text += "A polygon with vertices displayed in a counter-clockwise fashion is said ";
		text += "to have counter-clockwise winding. If this same polygon is flipped over, its ";
		text += "vertices would be displayed in a clockwise fashion.";
		text += "\n\n";
		text += "While it's arbitrary whether clockwise or counter-clockwise winding ";
		text += "represents front-facing polygons, it's common to use counter-clockwise. ";
		text += "This convention matches the right-hand rule used for vectors.";
		text += "\n\n";
		if (!glWidget->correctingWindingOrder()) {
			text += "The winding order of the top of the diamond is incorrectly ";
			text += "set. Since the winding order is used to determine if a ";
			text += "polygon is back-facing or not, the top is interpreted as ";
			text += "front-facing when it's really facing away from the camera, ";
			text += "and vice versa.";
			text += "\n\n";
			text += "There are two artifacts of this: the first is the top of the ";
			text += "diamond is incorrectly culled when it should be visible, ";
			text += "resulting in a hole. The second is that the top is rendered ";
			text += "when it should be behind the rest of the figure.";
			text += "\n\n";
			if (glWidget->usingDepthTesting()) {
				text += "The first artifact is not correctable (without correcting ";
				text += "the wind), but the second is corrected via the depth test. ";
				text += "The depth test is ensuring that the pixels nearest to the ";
				text += "camera. Since the incorrect winding does not change the depth ";
				text += "of individual pixels, the depth test is able to hide this ";
				text += "artifact.";
				text += "\n\n";
			} else {
				text += "While the first artifact is not correctable (without correcting ";
				text += "the wind), the second would be fixed by enabling the depth test. ";
				text += "The depth test would ensure only the geometry nearest to the ";
				text += "camera is rendered. Since the incorrect winding does not change the ";
				text += "depth of individual pixels, the depth test would correct this ";
				text += "artifact.";
				text += "\n\n";
			}
		} else if (glWidget->usingDepthTesting()) {
			assert (glWidget->correctingWindingOrder());
			text += "The depth test is ensuring that only the figures closest ";
			text += "to the camera are being rendered. Without it, figures would ";
			text += "be rendered in the order that they were provided, indiscriminately ";
			text += "occluding other geometry. However, in very simple cases like this one, ";
			text += "the back-face test is sufficient to generate a correct image.";
			text += "\n\n";
		} else {
			assert(glWidget->usingBackFaceCulling());
			assert(glWidget->correctingWindingOrder());
			assert(!glWidget->usingDepthTesting());
			text += "The depth test is not being performed. Front-facing geometry ";
			text += "will indiscriminately occlude previously rendered polygons. ";
			text += "However, in very simple cases like this one, the back-face test ";
			text += "is sufficient to generate a correct image.";
			text += "\n\n";
		}
		text += "Since back-face culling removes back-facing polygons, the 'Draw Backs as ";
		text += "Wireframes' would have no effect.";
	} else if (glWidget->usingDepthTesting()) {
		text += "The depth test is ensuring that only the figures closest ";
		text += "to the camera are being rendered. Without it, figures would ";
		text += "be rendered in the order provided, indiscriminately occluding ";
		text += "other geometry.";
		text += "\n\n";
		assert(!glWidget->usingBackFaceCulling());
		text += "Since the back-face culling test is not being performed, all polygons ";
		text += "are being rendered. While the depth test is sufficient to render a ";
		text += "correct looking image, the process is suboptimal.";
		text += "\n\n";
		text += "The depth test implicitly removes back-facing pixels, so the 'Draw Backs ";
		text += "as Wireframes' option is disabled. Also, since the depth test doesn't ";
		text += "consider winding, the 'Correct Winding Order' option is also disabled.";
		text += "option is disabled.";
	} else {
		assert(!glWidget->usingDepthTesting());
		assert(!glWidget->usingBackFaceCulling());
		text += "With no depth tests or back-face culling, only the order of rendering ";
		text += "matters. Polygons are rendered indiscriminately; they will appear on top ";
		text += "of previously drawn polygons regardless of their geometric relationship. ";
		text += "For example, the top of the diamond will always appear 'above' the rest of ";
		text += "the figure.";
		text += "\n\n";
		text += "This configuration would appear correct only if we ensured the scene is ";
		text += "always drawn back-to-front, commonly known as the 'painter's algorithm.'";
		text += "\n\n";
		if (glWidget->drawingBacksAsWireframes()) {
			text += "Back-facing polygons are being drawn as wireframes. This simulates ";
			text += "what the back-face culling operation would do. Enable that test ";
			text += "for more details on winding and back-facing polygon removal.";
		} else {
			text += "Since the winding order is not relevant in this configuration, the ";
			text += "'Correct Winding Order' option has been disabled.";
		}
	}
	descriptionLabel->setText(text);
}
