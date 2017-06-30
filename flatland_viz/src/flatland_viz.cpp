#include <QColor>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>

#include <OgreColourValue.h>
#include "rviz/display.h"
#include "rviz/render_panel.h"
#include "rviz/view_manager.h"
#include "rviz/visualization_manager.h"

#include "flatland_viz/flatland_viz.h"

FlatlandViz::FlatlandViz(QWidget* parent) : QWidget(parent) {
  // Construct and lay out render panel.
  render_panel_ = new rviz::RenderPanel();
  QVBoxLayout* main_layout = new QVBoxLayout;
  // main_layout->setSpacing(0);
  main_layout->setMargin(0);
  main_layout->addWidget(render_panel_);

  // Set the top-level layout for this FlatlandViz widget.
  setLayout(main_layout);

  // Next we initialize the main RViz classes.
  //
  // The VisualizationManager is the container for Display objects,
  // holds the main Ogre scene, holds the ViewController, etc.  It is
  // very central and we will probably need one in every usage of
  // librviz.
  manager_ = new rviz::VisualizationManager(render_panel_);
  render_panel_->initialize(manager_->getSceneManager(), manager_);
  manager_->initialize();
  manager_->startUpdate();

  // Set view controller to top down
  manager_->getViewManager()->setCurrentViewControllerType("rviz/TopDownOrtho");
  render_panel_->setBackgroundColor(Ogre::ColourValue(1, 1, 1));

  manager_->createDisplay("rviz/MarkerArray", "2d", true)
      ->subProp("Marker Topic")
      ->setValue("/flatland_server/debug/layer_2d");

  // Create a Grid display.
  grid_ = manager_->createDisplay("rviz/Grid", "adjustable grid", true);
  ROS_ASSERT(grid_ != NULL);

  // Configure the GridDisplay the way we like it.
  grid_->subProp("Line Style")->setValue("Billboards");
  grid_->subProp("Color")->setValue(QColor(Qt::black));
  grid_->subProp("Line Style")->subProp("Line Width")->setValue(0.1);
  grid_->subProp("Cell Size")->setValue(1.0);
}

// Destructor.
FlatlandViz::~FlatlandViz() { delete manager_; }
