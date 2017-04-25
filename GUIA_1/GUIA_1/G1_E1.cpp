#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <pdi_functions.h>
using namespace cv;
using namespace std;
using namespace pdi;


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
void crop_mouse() {
	//	//EJ2 inciso 1.. Utilizo la funcion "Mouse" definida arriba
	//	namedWindow("ImageDisplay", 1);
	//	setMouseCallback("ImageDisplay", Mouse, NULL);
	//	imshow("ImageDisplay", img);
	//	waitKey(10000);
	//	namedWindow("cropped", 1);
	//	int ancho = P2.x - P1.x;
	//	int alto = P2.y - P1.y;
	//	Rect r_crop(P1.x, P1.y, ancho, alto);
	//	cout << P1.x << ", " << P2.x << ", " << P1.y << ", " << P2.y << endl;
	//	Mat img_crop = img(r_crop);
	//	imshow("cropped", img_crop);
	//	waitKey(0);
	//	system("PAUSE");
}

	//RECORTAR PARTE DE UNA IMAGEN , QUEDANDONOS CON LA SUB IMAGEN
	void Crop_Img(string imagen) {
		imagen = "Imagenes\\" + imagen;
		Mat img = cv::imread(imagen, 1);
		Rect region_crop(10, 50, 630, 270); //VALORES A EDITAR
		Mat image_roi = img(region_crop);
		imshow("ROI", image_roi);
		cout << endl << endl;
		cout << "Info Imagen Original:" << endl << endl;
		info(img);
		cout << "Info Imagen ROI:" << endl << endl;
		info(image_roi);

	}
//Escalar imagen segun el ancho y alto que le pasemos
	Mat escalar(Mat src, int columnas, int filas) {
		Size tam(columnas, filas);//the dst image size,e.g.100x100
		Mat dst;//dst image
		//Mat src = imread(imagen, 1);  //src image
		resize(src, dst, tam);
		/*namedWindow("");
		imshow("w5", dst);
		waitKey(0);*/
		return dst;
	}
	//MOSTRAR IMAGEN E INFORMACION DE ESTA.
	void Mostrar_Img_Info(string imagen) {
		imagen = "Imagenes\\" + imagen;
		Mat img = cv::imread(imagen);
		//cv::Mat img = cv::imread("C:\\Users\\Operador\\Desktop\\CURSADO 2016\\Procesamiendo Digital de Imagenes\\Imagenes\\messi.jpg",1);
		if (img.empty() == true) {
			cerr << "La imagen no esta en el directorio" << endl;
		}
		else
		{
			namedWindow("w1");
			//imwrite("img_grey.jpg", img);
			info(img); //informacion de la imagen, ejercicio 1_2 size: filasXcolumnas
			imshow("w1", img);

			waitKey(0);
			
			//system("PAUSE");
			
		}
	}
	//ACCEDER AL VALOR DE (x,y) pixel y editarlo
	void Editar_pixel(string imagen,int x, int y) {
		imagen = "Imagenes\\" + imagen;
		Mat img = cv::imread(imagen,1);
		//A traves de un Vect3b accedo al valor de un pixel
		Vec3b px = img.at<Vec3b>(x, y);
		int b = px.val[0];
		int g = px.val[1];
		int r = px.val[2];

		cerr << "R: " << r << endl;
		cerr << "G: " << g << endl;
		cerr << "B: " << b << endl;

		Scalar pixel = px; // scalar v[4], orden [b g r 0]
		cerr << pixel << endl;
		//pongo el pixel en rojo
		px.val[0] = 0;
		px.val[1] = 0;
		px.val[2] = 255;
		img.at<Vec3b>(Point(x, y)) = px;
		pixel = px; // scalar v[4], orden [b g r 0]
		cerr << pixel << endl;
		namedWindow("w1");
		imshow("w1", img);
		waitKey(0);
		system("PAUSE");
	}

	
	//void ej2() {
	//	//EJ2 inciso 1.. Utilizo la funcion "Mouse" definida arriba
	//	namedWindow("ImageDisplay", 1);
	//	setMouseCallback("ImageDisplay", Mouse, NULL);
	//	imshow("ImageDisplay", img);
	//	waitKey(10000);
	//	namedWindow("cropped", 1);
	//	int ancho = P2.x - P1.x;
	//	int alto = P2.y - P1.y;
	//	Rect r_crop(P1.x, P1.y, ancho, alto);
	//	cout << P1.x << ", " << P2.x << ", " << P1.y << ", " << P2.y << endl;
	//	Mat img_crop = img(r_crop);
	//	imshow("cropped", img_crop);
	//	waitKey(0);
	//	system("PAUSE");
	//
	//	//EDITO ALGUNOS VALORES DE ALGUNOS PIXELS
	//	//cv::Mat img = cv::imread("futbol.jpg");
	//	//Before changing
	//	cv::imshow("Before", img);
	//	waitKey(10000);
	//	//change some pixel value
	//	cout << img.cols << endl;
	//	cout << img.rows << endl;
	//	for (int j = 0; j < img.rows - 1; j++)
	//	{
	//		for (int i = 0; i < img.cols - 1; i++)
	//		{
	//			//if (i == j)
	//			img.at<uchar>(j, i) = 255; //white
	//		}
	//	}
	//	//After changing
	//	cv::imshow("After", img);
	//	waitKey(10000);
	//	//system("PAUSE");
	//EJ2 inciso 2 -- GRAFICAR PERFIL DE INTENSIDAD SOBRE UNA DETERMINADA FILA O COLUMNA

	//Mat img1 = cv::imread("futbol.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//cerr << "Intensidad de la fila 1: " << endl;
	//namedWindow("original");
	//info(img1);
	//imshow("original", img1);
	//Mat dat_intensity(1, img1.rows, CV_8U);
	//for (int j = 0; j < img1.rows; j++) {
	//	dat_intensity.at<uchar>(j) = img1.at<uchar>(360, j);
	//	cout << "columna " << j << ": " << int(img1.at<uchar>(1, j)) << endl;
	//}
	//Mat grafico(400, 400, CV_8U);
	//grafico.setTo(Scalar(0, 0, 0));
	//draw_graph(grafico, dat_intensity);
	//imshow("Grafico intensidad", grafico);
	//waitKey(0);
	//system("PAUSE");
	//}

	}
	void botellas() {
		Mat bottle = imread("Imagenes\\botellas.tif", CV_LOAD_IMAGE_GRAYSCALE);
		info(bottle);
		namedWindow("Botellas");
		imshow("Botellas", bottle); 
		Rect r1(0, 0, 36, 185); Mat b1 = bottle(r1); int c1 = 0; Mat m1(1, b1.rows, CV_8U);
		Rect r2(48, 0, 60, 185); Mat b2 = bottle(r2); int c2 = 0; Mat m2(1, b2.rows, CV_8U);
		Rect r3(115, 0, 60, 185); Mat b3 = bottle(r3); int c3 = 0; Mat m3(1, b3.rows, CV_8U);
		Rect r4(182, 0, 60, 185); Mat b4 = bottle(r4); int c4 = 0; Mat m4(1, b4.rows, CV_8U);
		Rect r5(249, 0, 36, 185); Mat b5 = bottle(r5); int c5 = 0; Mat m5(1, b5.rows, CV_8U);
		for (int i = 0; i < b1.rows; i++) {
			m1.at<uchar>(i) = b1.at<uchar>(i, (b1.cols)/2);
			if (int(m1.at<uchar>(i)) > 250) {
				c1++;
				//cout << int(m1.at<uchar>(i)) << endl;
			}
			m2.at<uchar>(i) = b2.at<uchar>(i, (b2.cols)/2);
			if (int(m2.at<uchar>(i)) > 250) {
				c2 = c2 + 1;
			}
			m3.at<uchar>(i) = b3.at<uchar>(i, (b3.cols)/2);
			if (int(m3.at<uchar>(i)) > 250) {
				c3 = c3 + 1;
			}
			m4.at<uchar>(i) = b4.at<uchar>(i, (b4.cols)/2);
			if (int(m4.at<uchar>(i)) > 250) {
				c4 = c4 + 1;
			}
			m5.at<uchar>(i) = b5.at<uchar>(i, (b5.cols)/2);
			if (int(m5.at<uchar>(i)) > 250) {
				c5 = c5 + 1;
			}
		}
		int c[5] = { c1, c2, c3, c4, c5 };
		int maximo = -1;
		int imax = 0;
		for (int i = 0; i < 5; i++) {
			if (c[i] > maximo) {
				maximo = c[i];
				imax = i+1;
			}
		}
		float porcent = (float)maximo/bottle.rows*100;
		/*cout << c1 << " " << c2 << " " << c3 << " " << c4 << " " << c5 << endl;
		cout << maximo << " " << imax << " " << porcent << endl;*/
		cout <<"El porcentaje de vacio de la botella que tiene menos liquido (Botella Nro " << imax << ") es de " << porcent << endl;
		waitKey(0);
		system("PAUSE");
	}

	int main(void) {
		Mat img = cv::imread("C:\\Users\\Operador\\Desktop\\CURSADO 2016\\Procesamiendo Digital de Imagenes\\Imagenes\\messi.jpg", 1);
		//Mat 	img_ = cv::imread("C:\\Users\\Operador\\Desktop\\CURSADO 2016\\Procesamiendo Digital de Imagenes\\Imagenes\\messi.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		Mat img_1 = cv::imread("C:\\Users\\Operador\\Desktop\\CURSADO 2016\\Procesamiendo Digital de Imagenes\\Imagenes\\earth.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		Mat img_2 = cv::imread("C:\\Users\\Operador\\Desktop\\CURSADO 2016\\Procesamiendo Digital de Imagenes\\Imagenes\\esqueleto.tif", CV_LOAD_IMAGE_GRAYSCALE);
		/*cout << "Nombre de la imagen a cargar" << endl;
		char image[20];
		cin >> image;*/
		//Mostrar_Img_Info((string)image); //1_1 Y 1_2
		//Editar_pixel((string)image, 200, 30); //1_3
		//Crop_Img((string)image); //1_4
		//Suma(img_1, img_2);
		
		botellas();
		//waitKey(0);
		///EJ1 inciso 5 incompleto
		//Mat esc = escalar(img, 300, 300);

		waitKey(0);
};


