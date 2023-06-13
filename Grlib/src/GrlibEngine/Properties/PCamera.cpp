#include "GrlibEngine/Properties/PCamera.h"

//-------------------------------------------------------------------------------------------
// public
//-------------------------------------------------------------------------------------------

PCamera::PCamera(double hfov, double vfov, Vector dir_vector, double draw_distance, Canvas& canvas, HierarchyTop& renderable_hrch_top, Point& camera_pos) :
	_hfov(hfov), _vfov(vfov), _init_dir_vector(dir_vector), _cur_dir_vector(new Vector(dir_vector)), _look_at_point(*new Point(0.0, 0.0, 0.0)), _draw_distance(draw_distance), _canvas(canvas), 
	_renderable_hrch_top(renderable_hrch_top), _camera_pos(camera_pos), _x_ang(0), _y_ang(0), _z_ang(0) {
	this->_init_dir_vector.normalize();
	this->_cur_dir_vector->normalize();
	this->_cam_control = _cam_control_type::dir_vector;
}

/*PCamera::PCamera(double hfov, double vfov, Point look_at, double draw_distance, Canvas& canvas, HierarchyTop& renderable_hrch_top) :
	_hfov(hfov), _vfov(vfov), _dir_vector(new Vector()), _look_at_point(look_at), _draw_distance(draw_distance), _canvas(canvas),
	_renderable_hrch_top(renderable_hrch_top) {
	this->_cam_control = _cam_control_type::look_at;
}*/

void PCamera::execute() {
	this->_render();
}

void PCamera::rotate(double x, double y, double z) {
	_x_ang += x;
	_y_ang += y;
	_z_ang += z;
	Matrix rot_matrix(Matrix::xyz_rotation_matrix(_x_ang, _y_ang, _z_ang));
	Vector* rotated_dir_vec = new Vector(rot_matrix * _init_dir_vector);
	delete _cur_dir_vector;
	_cur_dir_vector = rotated_dir_vec;
}

//-------------------------------------------------------------------------------------------
// private
//-------------------------------------------------------------------------------------------

void PCamera::_render() const {
	std::vector<Ray>& cam_rays = this->_get_camera_rays();
	if (cam_rays.size() != this->_canvas.get_size()) {
		std::string err_str = "_get_camera_rays returned amount of rays that does not equal cells \
			count of canvas: cam_rays.size(): " + std::to_string(cam_rays.size()) + " | _canvas.get_size(): " +
			std::to_string(this->_canvas.get_size());
		throw PCameraException(err_str.c_str());
	}
	for (int i = 0; i < this->_canvas.rows_count(); i++) {
		for (int j = 0; j < this->_canvas.columns_count(); j++) {
			int cur_ray_ind = i * this->_canvas.columns_count() + j;
			Ray& cur_ray = cam_rays[cur_ray_ind];
			double& cur_cell = this->_canvas(i, j);
			double min_dist = -1;
			for (auto entity : _renderable_hrch_top.get_entity_list()) {
				PRenderable* prop = entity->get_property<PRenderable>();
				if (prop != nullptr) {
					double dist = prop->calc_dist(cur_ray);
					if (dist >= 0) {
						if (min_dist >= 0) {
							min_dist = std::min(dist, min_dist);
						}
						else {
							min_dist = dist;
						}
					}
				}
			}
			cur_cell = min_dist * abs((*this->_cur_dir_vector * cur_ray.get_dir_vector()));
		}		
	}
	cam_rays.clear();
}

std::vector<Ray>& PCamera::_get_camera_rays() const {
	std::vector<Ray>& raycasts = *new std::vector<Ray>();
	/*std::vector<Vector> camera_basis = BasisConverter::create_orth_3d(*this->_cur_dir_vector);
	Matrix trans_matrix(3, 3);
	trans_matrix.set_column(0, camera_basis[0]);
	trans_matrix.set_column(1, camera_basis[1]);
	trans_matrix.set_column(2, camera_basis[2]);*/
	int raycasts_count = _canvas.get_size();
	int height = _canvas.rows_count();
	int width = _canvas.columns_count();
	double delta_ver = _vfov / height;
	double delta_hor = _hfov / width;

	for (int i = 0; i < raycasts_count; i++) {
		auto test = static_cast<DataTable>(*this->_cur_dir_vector);
		Matrix raycast_dir_vec(test);
		int hor_i = i % width;
		int ver_i = i / width;
		double cur_ver_rot = delta_ver * ver_i - _vfov / 2;
		double cur_hor_rot = delta_hor * hor_i - _hfov / 2 + _z_ang;
		Matrix hor_rot = Matrix::z_rotation_matrix(cur_hor_rot);
		Matrix ver_rot = Matrix::y_rotation_matrix(cur_ver_rot);

		Matrix rotated_raycast_matrix(hor_rot * ver_rot * raycast_dir_vec);
		Vector rotated_raycast(rotated_raycast_matrix);
		raycasts.push_back(Ray(rotated_raycast, _camera_pos));
	}

	return raycasts;
}