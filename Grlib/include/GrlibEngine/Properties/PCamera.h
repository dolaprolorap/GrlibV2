#pragma once
#include "GrlibMath/Point.h"
#include "GrlibMath/BasisConverter.h"

#include "GrlibEngine/Ray.h"
#include "GrlibEngine/Canvas.h"
#include "GrlibEngine/Property.h"
#include "GrlibEngine/Canvas.h"
#include "GrlibEngine/HierarchyTop.h"
#include "GrlibEngine/properties.h"

#include "GrlibExceptions/EngineExceptions/Properties/PCameraException.h"

// Camera property
class PCamera : public Property {
public:
	// Create camera by horizontal field of view `hfov` (in angles), vertical field of view `vfov`, direction vector `dir_vector`,
	// draw distance `draw_distance`, canvas `canvas` and camera positions `camera_pos`
	PCamera(double hfov, double vfov, Vector dir_vector, double draw_distance, Canvas& canvas, HierarchyTop& renderable_hrch_top, Point& camera_pos);
	// Create camera by horizontal field of view `hfov` (in angles), vertical field of view `vfov`, look at point `look_at`,
	// draw distance `draw_distance` and canvas `canvas`	
	// FOR LATER VERSION
	//PCamera(double hfov, double vfov, Point look_at, double draw_distance, Canvas& canvas, HierarchyTop& renderable_hrch_top);

	// Render
	void execute() override;

	// Rotate 
	void rotate(double x, double y, double z);

private:
	// Angles above axis
	double _x_ang, _y_ang, _z_ang;
	// Render renderable objects of hierarchy and send data to the canvas
	void _render() const;
	// Get rays of camera cells
	std::vector<Ray>& _get_camera_rays() const;

	// Horizontal field of view in angles
	double _hfov;
	// Vertical field of view in angles
	double _vfov;
	// Draw distance
	double _draw_distance;

	// Types of camera movement is controlled 
	enum _cam_control_type {
		dir_vector, look_at
	};	
	// How camera is controlled
	_cam_control_type _cam_control;
	// Current direction vector
	Vector* _cur_dir_vector;
	// Start direction vector
	Vector _init_dir_vector;
	// Look at point
	Point& _look_at_point;

	// Canvas on which renderd pictures translates
	Canvas& _canvas;
	// Hierarchy top of objects, that will be rendered
	HierarchyTop& _renderable_hrch_top;
	
	// Camera position
	Point& _camera_pos;
};