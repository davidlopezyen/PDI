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

void ver_histo(Mat img) {
	//Mat img = imread("Imagenes\\Busqueda_histograma\\Caricaturas04.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//Mat img1 = imread("Imagenes\\billete.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat canvas(img.rows, img.cols, CV_32F);
	Mat hist = histogram(img, 255);
	normalize(hist, hist, 0, 1, CV_MINMAX);
	draw_graph(canvas, hist);

	imshow("Image", img);
	imshow("Histogram sin equailizar", canvas);
	//cout << hist << endl;
	/*
	Mat ecualizado;
	equalizeHist(img, ecualizado);
	imshow("Imagen ecualizada", ecualizado);
	Mat canvas2(ecualizado.rows, ecualizado.cols, CV_32F);
	Mat hist_e = histogram(ecualizado, 255);
	normalize(hist_e, hist_e, 0, 1, CV_MINMAX);
	draw_graph(canvas2, hist_e);
	imshow("Histograma equalizado", canvas2);*/
}
Mat filtro_pasa_bajos(int tam) {
	Mat kernel = Mat::ones(tam, tam, CV_32F) / pow(tam, 2);
	return kernel;
}
Mat filtro_gaussiano(int tam, int sigma) {
	int shift = tam / 2;
	Mat kernel(tam, tam, CV_32F);
	double r; double s = pow(sigma, 2) * 2.0;
	double sum = 0;
	double num,den = (M_PI*s);
	for (int x = -shift; x <= shift; x++) {
		for (int y = -shift; y <= shift; y++) {
			r = pow(x, 2) + pow(y, 2);
			num = exp(-r / s);
			kernel.at<float>(x + shift, y + shift) = num / den;
			sum += kernel.at<float>(x + shift, y + shift);
		}
	}
	for (int i = 0; i < tam; ++i)
		for (int j = 0; j < tam; ++j)
			kernel.at<float>(i, j) /= sum;

	return kernel;
}
Mat filtro_pasa_alto_suma1(int tam) {
	Mat kernel(tam, tam, CV_32F);
	for (int i = 0; i<kernel.rows; i++) {
		for (int j = 0; j<kernel.cols; j++) {
			kernel.at<float>(i, j) = -1;
		}
	}
	kernel.at<float>(tam / 2, tam / 2) = tam*tam;
	return kernel;
}

Mat filtro_pasa_alto_suma0(int tam) {
	Mat kernel(tam, tam, CV_32F);
	for (int i = 0; i<kernel.rows; i++) {
		for (int j = 0; j<kernel.cols; j++) {
			kernel.at<float>(i, j) = -1;
		}
	}
	kernel.at<float>(tam / 2, tam / 2) = tam*tam-1;
	return kernel;
}
		
void Ej2_1() {
	Mat img = imread("Imagenes\\huang1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat k3, k4, k6, k10,k30;
	k3 = filtro_pasa_bajos(3); k4 = filtro_pasa_bajos(4); k6 = filtro_pasa_bajos(6); k10 = filtro_pasa_bajos(10); k30 = filtro_pasa_bajos(30);
	Mat f3, f4, f6, f10,f30;
	f3 = convolve(img, k3);
	f4 = convolve(img, k4);
	f6 = convolve(img, k6);
	f10 = convolve(img, k10);
	f30 = convolve(img, k30);
	//imshow("img", img);
	//imshow("k3", f3);
	//imshow("k4", f4);
	//imshow("k6", f6); 
	//imshow("k10", f10);
	//imshow("k30",f30);
	//
	vector<Mat> images;
	images.push_back(img); images.push_back(f3); images.push_back(f4); images.push_back(f6); images.push_back(f10); images.push_back(f30);
	Mat m = mosaic(images, 3);
	//putText(img, text, textOrg, fontFace, fontScale,Scalar::all(255), thickness, 8);
	putText(m,"Imagen Original", cvPoint(img.cols * 0 + 50, img.rows - 5), FONT_HERSHEY_COMPLEX_SMALL , 1, cvScalar(255, 255, 255),1, 4);
	putText(m, "Kernel 3x3", cvPoint(img.cols * 1 + 50, img.rows - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255),1, 4);
	putText(m, "Kernel 4x4", cvPoint(img.cols * 2 + 50, img.rows - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255),1, 4);
	putText(m, "Kernel 6x6", cvPoint(img.cols * 0 + 50, img.rows*2 - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255),1, 4);
	putText(m, "Kernel 10x10", cvPoint(img.cols * 1 + 50, img.rows*2 - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255),1, 4);
	putText(m, "Kernel 30x30", cvPoint(img.cols * 2 + 50, img.rows*2 - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255),1, 4);
	imshow("Filtro PasaBajos", m);
}
void Ej2_2() {
	Mat img = imread("Imagenes\\huang1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat f1_33, f5_33, f10_33, f1_55, f5_55,f10_55;
	/*Mat k1_33 = filtro_gaussiano(3, 1);
	Mat k2_33 = filtro_gaussiano(3,2);
	Mat k5_33 = filtro_gaussiano(3,5);
	Mat k1_55 = filtro_gaussiano(5,1); 
	Mat k5_55 = filtro_gaussiano(5,5);
	Mat k10_55 = filtro_gaussiano(5,10);
	f1_33 = convolve(img, k1_33);
	f5_33 = convolve(img, k5_33);
	f10_33 = convolve(img, k10_33);
	f1_55 = convolve(img, k1_55);
	f5_55 = convolve(img, k5_55);
	f10_55= convolve(img, k10_55);*/

	//filtro gaussiano de opencv, igual a las definiciones de arriba.
	GaussianBlur(img, f1_33, Size(3, 3), 1);
	GaussianBlur(img, f5_33, Size(3, 3), 5);
	GaussianBlur(img, f10_33, Size(3, 3), 10);
	GaussianBlur(img, f1_55, Size(5, 5), 1);
	GaussianBlur(img, f5_55, Size(5, 5), 5);
	GaussianBlur(img, f10_55, Size(5, 5), 10);

	vector<Mat> images;
	images.push_back(img); images.push_back(f1_33); images.push_back(f5_33); images.push_back(f10_33);
	images.push_back(f1_55); images.push_back(f5_55); images.push_back(f10_55);
	Mat m = mosaic(images, 2);
	//putText(img, text, textOrg, fontFace, fontScale,Scalar::all(255), thickness, 8);
	putText(m, "Imagen Original", cvPoint(img.cols * 0 + 50, img.rows - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	putText(m, "Kernel 3x3 - o = 1", cvPoint(img.cols * 1 + 50, img.rows - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	putText(m, "Kernel 3x3 - o = 5", cvPoint(img.cols * 2 + 50, img.rows - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	putText(m, "Kernel 3x3 - o = 10", cvPoint(img.cols * 3 + 50, img.rows - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	putText(m, "Kernel 5x5 - o = 1", cvPoint(img.cols * 0 + 50, img.rows * 2 - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	putText(m, "Kernel 5x5 - o = 5", cvPoint(img.cols * 1 + 50, img.rows * 2 - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	putText(m, "Kernel 5x5 - o = 10", cvPoint(img.cols * 2 + 50, img.rows * 2 - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	imshow("Filtro Gaussiano", m);
}
Mat escalar(Mat src, int columnas, int filas) {
	Size tam(columnas, filas);//the dst image size,e.g.100x100
	Mat dst;//dst image
	resize(src, dst, tam);
	/*namedWindow("");
	imshow("w5", dst);
	waitKey(0);*/
	return dst;
}
void Ej2_3() { //filtro pasa bajos para localizar objetos grandes
	Mat img = imread("Imagenes\\hubble.tif", CV_LOAD_IMAGE_GRAYSCALE);
	Mat filtro = filtro_pasa_bajos(3);
	//info(img);
	//system("PAUSE");
	Mat img_f = convolve(img, filtro);
	Mat Resaltada(img_f.size(), CV_8UC(1));
	for (int i = 0; i < img_f.rows; i++) {
		for (int j = 0; j < img_f.cols; j++) {
			if ((int)img_f.at<uchar>(i, j) > 130) {
				Resaltada.at<uchar>(i, j) = 255;
			}
			else
				Resaltada.at<uchar>(i, j) = 0;
		}
	}
	imshow("Original", img);
	imshow("Filtrado", img_f);
	imshow("Umbral Binario", Resaltada);
}
void Ej3_1_2() {
	Mat img = imread("Imagenes\\huang1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//Mat img = imread("Imagenes\\camaleon.tif", CV_LOAD_IMAGE_GRAYSCALE);
	Mat k1, k2, k3, k4, k5, k6;
	k1 = filtro_pasa_alto_suma1(3);
	k2 = filtro_pasa_alto_suma1(5);
	k3 = filtro_pasa_alto_suma1(7);
	k4 = filtro_pasa_alto_suma0(3);
	k5 = filtro_pasa_alto_suma0(5);
	k6 = filtro_pasa_alto_suma0(7);
	Mat f1, f2, f3, f4, f5, f6;
	f1 = convolve(img, k1);
	f2 = convolve(img, k2);
	f3 = convolve(img, k3);
	f4 = convolve(img, k4);
	f5 = convolve(img, k5);
	f6 = convolve(img, k6);
	vector<Mat> images;
	images.push_back(img); images.push_back(f1); images.push_back(f2); images.push_back(f3); images.push_back(img); images.push_back(f4); images.push_back(f5); images.push_back(f6);
	Mat m = mosaic(images, 2);
	putText(m, "Imagen Original", cvPoint(img.cols * 0 + 50, img.rows - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	putText(m, "Kernel 3x3", cvPoint(img.cols * 1 + 50, img.rows - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	putText(m, "Kernel 5x5", cvPoint(img.cols * 2 + 50, img.rows - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	putText(m, "Kernel 7x7", cvPoint(img.cols * 3 + 50, img.rows - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	putText(m, "Imagen Original", cvPoint(img.cols * 0 + 50, (img.rows - 5) * 2), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	putText(m, "Kernel 3x3", cvPoint(img.cols * 1 + 50, (img.rows - 5) * 2), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	putText(m, "Kernel 5x5", cvPoint(img.cols * 2 + 50, (img.rows - 5) * 2), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	putText(m, "Kernel 7x7", cvPoint(img.cols * 3 + 50, (img.rows - 5) * 2), FONT_HERSHEY_COMPLEX_SMALL, 1, cvScalar(255, 255, 255), 1, 4);
	imshow("Filtros pasa altos suma 1 fila 1 - Filtros pasa altos suma 0 fila 2 ", m);
}
void Ej4_1() {
	Mat img = imread("Imagenes\\camaleon.tif", CV_LOAD_IMAGE_GRAYSCALE);
	Mat kernel = filtro_pasa_bajos(25); //A MEDIDA QUE AUMENTO EL TAMAÑO DEL KERNEL LA MASCARA DIFUSA RESALTA MEJOR LOS DETALLES DE LA IMAGEN
	Mat filtrada = convolve(img, kernel);
	Mat difusa = (img - filtrada + 255) / 2;
	imshow("Original", img);
	imshow("Filtro Pasa Bajos", filtrada);
	imshow("Mascara Difusa", difusa);
}
void Ej4_2(float A) {
	Mat img = imread("Imagenes\\camaleon.tif", CV_LOAD_IMAGE_GRAYSCALE);
	Mat kernel = filtro_pasa_bajos(15);
	Mat filtrada = convolve(img, kernel);
	Mat alta_potencia = (A * img - filtrada + 255) / 2;
	imshow("Original", img);
	imshow("Filtro Pasa Bajos", filtrada);
	imshow("Alta Potencia", alta_potencia);
}

void Dybala() {
	Mat dymask = imread("Imagenes\\dybalamask2.jpg", 1);
	Mat dy = imread("Imagenes\\dybala.jpg", 1);
	Mat dymask_e = escalar(dymask, 400, 400);
	Mat dy_e = escalar(dy, 400, 400);
	/*imshow("Mask", dymask_e);
	imshow("Dybala", dy_e);*/
	vector<Mat> images;
	images.push_back(dy_e); images.push_back(dymask_e);
	Mat m = mosaic(images, 1);
	imshow("M", m);
}
void Ej5_1() {
	//Lectura e histograma de la imagen original
	Mat img = imread("Imagenes\\cuadros.tif", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Original", img);
	//Ecualizo globalmente la imagen original y se puede ver que al haber la 
	//mayor parte de la imagen en blanco, se ecualiza de mal forma obteniendo 
	//una imagen como si tuviera ruido.
	Mat img2;
	equalizeHist(img, img2);
	imshow("Ecualizacion Global", img2);
	//Ecualizo por partes (localmente):
	Mat cuadro1 = img(Rect(12, 12, 124, 124));
	equalizeHist(cuadro1, cuadro1);
	Mat cuadro2 = img(Rect(374, 12, 124, 124));
	equalizeHist(cuadro2, cuadro2);
	Mat cuadro3 = img(Rect(194, 194, 124, 124));
	equalizeHist(cuadro3, cuadro3);
	Mat cuadro4 = img(Rect(12, 374, 124, 124));
	equalizeHist(cuadro4, cuadro4);
	Mat cuadro5 = img(Rect(374, 374, 124, 124));
	equalizeHist(cuadro5, cuadro5);
	imshow("Ecualizacion Local", img);
	waitKey(0);
	
}
int main(void) {
	Mat img = imread("Imagenes\\huang1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//ver_histo(img);
	//Ej2_1();
	//Ej2_2();
	//Ej2_3();
	//Ej3_1_2();
	//Ej4_1();
	//Ej4_2(2.1);
	Ej5_1();
	waitKey(0);

};