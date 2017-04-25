//usados para recortar una imagen a partir de otra
Rect cropRect(0, 0, 0, 0);
Point P1(0, 0);
Point P2(0, 0);

void Mouse(int event, int x, int y, int flags, void* userdata) {
	int x_ini = 0; int y_ini = 0; int x_fin = 0; int y_fin = 0;

	switch (event) {
	case CV_EVENT_LBUTTONDOWN:
		P1.x = x;
		P1.y = y;
		P2.x = x;
		P2.y = y;
		cout << "Boton izquierdo presionado en las coord (x, y): " << x << " , " << y << endl;
		break;
	case CV_EVENT_LBUTTONUP:
		P2.x = x;
		P2.y = y;
		cout << "Boton izquierdo liberado en las coord (x,y): " << x << " , " << y << endl;
		break;
	default: break;
	}
}
void crop_mouse(string image) {
	//	Utilizo la funcion "Mouse" definida arriba. Solo recortar desde arriba-izq hacia abajo-derecha
		Mat img = imread(image, 1);
		namedWindow("ImageDisplay", 1);
		setMouseCallback("ImageDisplay", Mouse, NULL);
		imshow("ImageDisplay", img);
		waitKey(10000);
		
		int ancho = P2.x - P1.x;
		int alto = P2.y - P1.y;
		Rect r_crop(P1.x, P1.y, ancho, alto);
		cout << P1.x << ", " << P2.x << ", " << P1.y << ", " << P2.y << endl;
		Mat img_crop = img(r_crop);
		namedWindow("cropped", 1);
		imshow("cropped", img_crop);
		waitKey(0);
		system("PAUSE");
	
}