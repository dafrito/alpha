#include <QtGui>
#include <cassert>
#include <QBoxLayout>
#include <QScrollArea>

#include "DiamondGLWidget.hpp"
#include "DiamondGLDemo.hpp"

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

	descriptionLabel->setTextFormat(Qt::RichText);

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
	descriptionScrollPanel->setFixedWidth(350);
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
		text += "<h4>Back-face Culling</h4>"
			"Polygons that are back-facing are being removed. The facing of a polygon "
			"is determined using the <b>winding order</b> of its vertices. "
			"A polygon with vertices displayed in a counter-clockwise fashion is said "
			"to have counter-clockwise winding. If this same polygon is flipped over, its "
			"vertices would be displayed in a clockwise fashion."
			"<p>"
			"While it is arbitrary whether clockwise or counter-clockwise winding "
			"represents front-facing polygons, it's common to use the latter. "
			"This convention matches the <b>right-hand rule</b> used for vectors."
			"<p>";
		if (!glWidget->correctingWindingOrder()) {
			text += "<h4>Incorrect Winding Order</h4>"
				"The winding order of the top of the diamond is incorrectly "
				"set. Since the winding order is used to determine if a "
				"polygon is back-facing or not, the top is interpreted as "
				"front-facing when it's really facing away from the camera, "
				"and vice versa."
				"<p>"
				"There are two visible artifacts of this mistake:"
				"<ul>"
				"<li>The top of the diamond is incorrectly hidden when it should be visible"
				", resulting in a hole."
				"<li>The top is rendered when it should be behind the rest of the figure. "
				"This may be corrected by the depth test."
				"</ul>"
				"<p>";
			if (glWidget->usingDepthTesting()) {
				text += "<h4>Depth Testing</h4>"
					"The depth test is ensuring that only the figures closest "
					"to the camera are being rendered. Without it, figures would "
					"be rendered in the order that they were provided, indiscriminately "
					"occluding other geometry. The depth test is able to correct the second "
					"artifact since the top of the diamond is behind the rest of the figure "
					"regardless of its winding order."
					"<p>";
			}
		} else if (glWidget->usingDepthTesting()) {
			assert (glWidget->correctingWindingOrder());
			text += "<h4>Depth Testing</h4>"
				"The depth test is ensuring that only the figures closest "
				"to the camera are being rendered. Without it, figures would "
				"be rendered in the order that they were provided, indiscriminately "
				"occluding other geometry. However, in very simple cases like this one, "
				"the back-face test is sufficient to generate a correct image."
				"<p>";
		} else {
			assert(glWidget->usingBackFaceCulling());
			assert(glWidget->correctingWindingOrder());
			assert(!glWidget->usingDepthTesting());
			text += "<h4>Depth Testing</h4>"
				"The depth test is not being performed. Front-facing geometry "
				"will indiscriminately occlude previously rendered polygons. "
				"However, in very simple cases like this one, the back-face test "
				"is sufficient to generate a correct image."
				"<p>";
		}
		text += "Since back-face culling removes back-facing polygons, the <b>Draw Backs as ";
		text += "Wireframes</b> option would have no effect.";
	} else if (glWidget->usingDepthTesting()) {
		text += "<h4>Depth Testing</h4>"
			"The depth test is ensuring that only the figures closest "
			"to the camera are being rendered. Without it, figures would "
			"be rendered in the order provided, indiscriminately occluding "
			"other geometry."
			"<p>";
		assert(!glWidget->usingBackFaceCulling());
		text += "Since the back-face culling test is not being performed, all polygons "
			"are being rendered. While the depth test is sufficient to render a "
			"correct looking image, the process is suboptimal."
			"<p>"
			"The depth test implicitly removes all back-facing pixels in this scene , so "
			"the <b>Draw Backs as Wireframes</b> option is disabled. Since the depth test "
			"doesn't consider winding, the <b>Correct Winding Order</b> option is also disabled."
			"<p>";
	} else {
		assert(!glWidget->usingDepthTesting());
		assert(!glWidget->usingBackFaceCulling());
		text += "<h4>Painter's Algorithm</h4>"
			"With no depth tests or back-face culling, only the order of rendering "
			"matters. Polygons are rendered indiscriminately; they will appear on top "
			"of previously drawn polygons regardless of their geometric relationship. "
			"For example, the top of the diamond will always appear in front of the rest of "
			"the figure."
			"<p>"
			"This configuration would appear correct only if we ensured the scene is "
			"always drawn back-to-front, commonly known as the <i>painter's algorithm</i>."
			"<p>";
		if (glWidget->drawingBacksAsWireframes()) {
			text += "Back-facing polygons are being drawn as wireframes. This simulates "
				"what the back-face culling operation would do. Enable that test "
				"for more details on winding and back-facing polygon removal.";
		} else {
			text += "Since the winding order is not relevant in this configuration, the "
				"<b>Correct Winding Order</b> option has been disabled.";
		}
	}
	descriptionLabel->setText(text);
}
