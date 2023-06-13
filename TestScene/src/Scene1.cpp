#include <windows.h>
#include <fstream>
#include <iostream>

#include "Grlib.h"

IdentifierList& il = *new IdentifierList();
CoordinateSystem& cs = *new CoordinateSystem(Point(0., 0., 0.));
Scene& scene1 = *new Scene(il, cs);
Entity& player = scene1.create_entity(*new Point(-7., 0., 0.));
Canvas& canvas = *new Canvas(27, 105);
PCamera& camera = *new PCamera(80., 60., *new Vector(1., 0., 0.), 9., canvas, scene1, player.coords);
ConsoleDraw& cd = *new ConsoleDraw(&canvas, 0, 9);
PMovement& move = *new PMovement(player.coords);

struct KeyHandler {
	void operator()(unsigned int key_id) {
		Vector* dir;
		switch (key_id) {
		case 'W':
		case 'w':
			dir = new Vector(1., 0., 0.);
			break;
		case 'S':
		case 's':
			dir = new Vector(-1., 0., 0.);
			break;
		case 'A':
		case 'a':
			dir = new Vector(0., -1., 0.);
			break;
		case 'D':
		case 'd':
			dir = new Vector(0., 1., 0.);
			break;
		case 'Q':
		case 'q':
			camera.rotate(0, 0, -15);
			dir = new Vector(0., 0., 0.);
			break;
		case 'E':
		case 'e':
			camera.rotate(0, 0, 15);
			dir = new Vector(0., 0., 0.);
			break;
		default:
			dir = new Vector(0., 0., 0.);
			break;
		}
		move.move(*dir);
		delete dir;
		camera.execute();
		cd.draw();
	}
};

int main() {
	EventSystem::init();
	KeyHandler kh;
	EventSystem::on_key_pressed.add_func(&kh);

	Entity& ellipsoid = scene1.create_entity(*new Point(0., 0., 0.));
	Entity& plane = scene1.create_entity(*new Point(0., 0., 0.));

	PRenderable* plane_prop = new PRenderablePlane(Vector(0., 0., 1.), Point(0., 0., -0.3));
	PRenderable* ellips_prop = new PRenderableEllipsoid(Point(0., 0., 1.), 1, 1, 1);

	ellipsoid.add_property<PRenderable>(ellips_prop);
	plane.add_property<PRenderable>(plane_prop);

	while (true) {
		EventSystem::handle();
	}

	return 0;
}