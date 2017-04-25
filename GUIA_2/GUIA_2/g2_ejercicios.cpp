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


void tranf_lineal(float a, float c) {
	Mat img = imread("Imagenes\\messi.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Original", img);
	Mat lut(1, 256, CV_8U);
	float s; 
	for (int r = 0; r<255; r++) {
		s = a * r + c;
		if (s>255) s = 255;
		if (s<0) s = 0;
		lut.at<unsigned char>(r) = s;
	}

	Mat grafico(255, 255, CV_8U);
	grafico.setTo(Scalar(0, 0, 0));
	draw_graph(grafico, lut);
	imshow("Grafico LUT", grafico);
	Mat output;
	LUT(img, lut, output);
	normalize(output, output, 0, 255, CV_MINMAX);

	//display the image:
	namedWindow("Salida", 1);
	imshow("Salida", output);
}
void LUTS(float a, float c,Mat img) {
	imshow("Original", img);
	Mat lut(1, 256, CV_8U);
	float s;
	for (int r = 0; r<255; r++) {
		s = a * r + c;
		if (s>225) s = 255;
		if (s > 100 && s < 200) s = 200;
		if (s<0) s = 0;
		lut.at<unsigned char>(r) = s;
	}

	Mat grafico(255, 255, CV_8U);
	grafico.setTo(Scalar(0, 0, 0));
	draw_graph(grafico, lut);
	imshow("Grafico LUT", grafico);
	Mat output;
	LUT(img, lut, output);
	normalize(output, output, 0, 255, CV_MINMAX);

	//display the image:
	namedWindow("Salida", 1);
	imshow("Salida", output);
}
void negativo(Mat m) {

	if (m.channels() == 3) {
		Vec3b pixel;
		for (int j = 0; j < m.rows; j++) {
			for (int i = 0; i < m.cols; i++) {
				pixel = m.at<Vec3b>(j, i);
				for (int k = 0; k < 3; k++) {
					int a = 255 - (int)pixel[k];
					m.at<Vec3b>(j, i)[k] = (uchar)a;
				}
			}
		}
	}
	else if (m.channels() == 1) {
		//vector<int>valores(256, 0);
		for (int j = 0; j < m.rows; j++) {
			waitKey(10);
			for (int i = 0; i < m.cols; i++) {
				uchar pixel = m.at<uchar>(j, i);
				int n = 255 - (int)pixel;
				m.at<uchar>(j, i) = n;
			}
		}
	}
	imshow("Negativo", m);
}
void transf_nolineal(int tipo, int c, float gamma, Mat img)  { //earth.bmp p ver magia
	Mat aux(1, 256, CV_8UC(1)); 
	if (tipo == 1) { //transformacion LOGARITMICA
		for (int r = 0; r < 255; r++) {
			float s = (255 / log(1 + 255))*log(1 + r);
			if (s>255) s = 255;
			if (s<0) s = 0;
			aux.at<unsigned char>(r) = s;
		}
	}
	else { //transformacion de POTENCIA
		for (int r = 0; r < 255; r++) {
			float s = (255 / pow(255, gamma))*pow(r, gamma);
			if (s>255) s = 255;
			if (s<0) s = 0;
			aux.at<unsigned char>(r) = s;
		}
	}
	Mat resultado;
	LUT(img, aux, resultado);
	Mat grafico(256, 256, CV_8U(1));
	grafico.setTo(Scalar(0, 0, 0));
	draw_graph(grafico, aux);
	imshow("Mapeo", grafico);
	imshow("original", img);
	imshow("Transformacion", resultado);
}


//Escalar imagen segun el ancho y alto que le pasemos
	Mat escalar(Mat src, int columnas, int filas) {
		Size tam(columnas, filas);//the dst image size,e.g.100x100
		Mat dst;//dst image
		resize(src, dst, tam);
		/*namedWindow("");
		imshow("w5", dst);
		waitKey(0);*/
		return dst;
	}
	void Suma(Mat img1, Mat img2) {
		//suma de dos imagenes
		Mat img1_esc = escalar(img1, 200, 200);
		Mat img2_esc = escalar(img2, 200, 200);
		Mat suma = (img1_esc + img2_esc) / 2;
		namedWindow("SUMA");
		imshow("SUMA", suma);
		
	}
	void Resta(Mat img1, Mat img2) {
		Mat img1_esc = escalar(img1, 200, 200);
		Mat img2_esc = escalar(img2, 200, 200);
		Mat resta = ((img1_esc - img2_esc) + 255) / 2;
		namedWindow("RESTA");
		imshow("RESTA", resta);
	}
	void Multiplicacion(Mat img) {

		Mat mascara = Mat::zeros(img.size(), img.type());
		Mat multiplicacion = Mat::zeros(img.size(), img.type());
	
		//SI LA MASCARA BINARIA ES UN RECTANGULO
		info(img);
		rectangle(mascara, Point(100, 80), Point(160, 155), Scalar(255, 0, 0), -1, 8, 0);
		//Now you can copy your source image to destination image with masking
		img.copyTo(multiplicacion, mascara);
		imshow("Imagen",img);
		imshow("Mask", mascara);
		imshow("multiplicacion", multiplicacion);

	}
	void Ejercicio3_2(Mat img) {
		//Mat img = imread("huang1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		Mat aux;
		img.convertTo(aux, CV_32F);
		vector<Mat> imagenes;
		for (int i = 0; i<50; i++) {
			Mat ruido(img.size(), img.type());
			randn(ruido, 0, 0.5 * 255);
			Mat resultado = (aux + ruido) / 2;
			imagenes.push_back(resultado);
		}
		Mat mezcla = imagenes[0];
		for (int i = 1; i<imagenes.size(); i++) {
			mezcla += imagenes[i];
		}
		mezcla /= imagenes.size();
		imshow("Original", img);
		imshow("Ruido", imagenes[0]);
		imshow("Resultado", mezcla);

	}
	void Ejercicio5_2(Mat entrada) {
		info(entrada);
		Mat img1 = imread("a7v600-SE.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		Mat img2 = imread("a7v600-X.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		info(img1);
		info(img2);
		imshow("SE", img1);
		imshow("X", img2);

		Mat mask = Mat::zeros(img2.size(), img2.type());
		mask(Rect(img2.rows / 2 - 10, img2.cols / 2 - 120, 100, 100)) = 1;
		Mat resultadox;
		img2.copyTo(resultadox, mask);
		imshow("X", resultadox);
		Mat maskx = Mat::zeros(img1.size(), img1.type());
		maskx(Rect(img1.rows / 2 - 10, img1.cols / 2 - 120, 100, 100)) = 1;
		Mat resultadose;
		img1.copyTo(resultadose, maskx);

		imshow("se", resultadose);
		float x = 0;float se = 0;

		for (int i = 150; i<250; ++i) {
			x += (float)resultadox.at<uchar>(116, i);
			se += (float)resultadose.at<uchar>(116, i);
		}
		x /= (250 - 150);
		se /= (250 - 150);

		cout << "Promedio de X: " << x << endl << "Promedio de SE: " << se << endl;

		Mat mask_input = Mat::zeros(entrada.size(), entrada.type());
		mask_input(Rect(entrada.rows / 2 - 10, entrada.cols / 2 - 120, 100, 100)) = 1;
		Mat resultado_entrada;
		entrada.copyTo(resultado_entrada, mask_input);

		float in = 0;

		for (int i = 150; i<250; ++i) {
			in += (float)resultado_entrada.at<uchar>(116, i);
		}
		in /= (250 - 150);
		cout << "Promedio de la entrada: " << in << endl << endl;
		if (abs(in - x) < abs(in - se)) {
			cout << "La placa es A7V600-x" << endl;
		}
		else {
			cout << "La placa es A7V600-SE" << endl;
		}
	}

	void Ejercicio5_3(Mat img) {
		//Mat img = imread(nombre, CV_LOAD_IMAGE_GRAYSCALE);
		Mat mascara = Mat::zeros(img.size(), img.type());
		Mat multiplicacion = Mat::zeros(img.size(), img.type());
		//SI LA MASCARA BINARIA ES UN CIRCULO
		circle(mascara, Point(53, 54), 16, Scalar(255, 0, 0), -1, 8, 0);
		circle(mascara, Point(102, 53), 16, Scalar(255, 0, 0), -1, 8, 0);
		circle(mascara, Point(152, 53), 16, Scalar(255, 0, 0), -1, 8, 0);
		circle(mascara, Point(202, 53), 16, Scalar(255, 0, 0), -1, 8, 0);
		circle(mascara, Point(252, 51), 16, Scalar(255, 0, 0), -1, 8, 0);

		circle(mascara, Point(53, 101), 16, Scalar(255, 0, 0), -1, 8, 0);
		circle(mascara, Point(102, 102), 16, Scalar(255, 0, 0), -1, 8, 0);
		circle(mascara, Point(152, 101), 16, Scalar(255, 0, 0), -1, 8, 0);
		circle(mascara, Point(202, 100), 16, Scalar(255, 0, 0), -1, 8, 0);
		circle(mascara, Point(252, 100), 16, Scalar(255, 0, 0), -1, 8, 0);
		//SI LA MASCARA BINARIA ES UN RECTANGULO
		info(img);
		imshow("Mascara", mascara);
		//	rectangle(mascara,Point(190,90),Point(250,155),Scalar(255, 0, 0),-1,8,0);
		//Now you can copy your source image to destination image with masking
		img.copyTo(multiplicacion, mascara);
		imshow("Blister", img);
		if ((int)img.at<uchar>(Point(53, 54))<100) cout << "El blister esta incompleto. Faltante en: " << Point(53, 54) << endl;
		if ((int)img.at<uchar>(Point(102, 53))<100) cout << "El blister esta incompleto. Faltante en: " << Point(102, 53) << endl;
		if ((int)img.at<uchar>(Point(152, 53))<100) cout << "El blister esta incompleto. Faltante en: " << Point(152, 53) << endl;
		if ((int)img.at<uchar>(Point(202, 53))<100) cout << "El blister esta incompleto. Faltante en: " << Point(202, 53) << endl;
		if ((int)img.at<uchar>(Point(252, 51))<100) cout << "El blister esta incompleto. Faltante en: " << Point(252, 51) << endl;
		if ((int)img.at<uchar>(Point(53, 101))<100) cout << "El blister esta incompleto. Faltante en: " << Point(53, 101) << endl;
		if ((int)img.at<uchar>(Point(102, 102))<100) cout << "El blister esta incompleto. Faltante en: " << Point(102, 102) << endl;
		if ((int)img.at<uchar>(Point(152, 101))<100) cout << "El blister esta incompleto. Faltante en: " << Point(152, 101) << endl;
		if ((int)img.at<uchar>(Point(202, 100))<100) cout << "El blister esta incompleto. Faltante en: " << Point(202, 100) << endl;
		if ((int)img.at<uchar>(Point(252, 100))<100) cout << "El blister esta incompleto. Faltante en: " << Point(252, 100) << endl;



		//	imshow("Imagen",img);
		
		imshow("Zona de interes", multiplicacion);
		imshow("Blister", img);
	}
int main(void) {
	
	
	Mat img1 = imread("Imagenes\\mosquito.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2 = imread("Imagenes\\messi.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img3 = imread("Imagenes\\earth.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img4 = imread("Imagenes\\rmn.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img5 = imread("Imagenes\\huang1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat blister_comp = imread("Imagenes\\blister_completo.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat blister_incomp = imread("Imagenes\\blister_incompleto.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat placa_x = imread("Imagenes\\a7v600-X.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat placa_se = imread("Imagenes\\a7v600-SE.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	//tranf_lineal(0.1, 1);
	//negativo(img);
	//LUTS(0.5, 0.7,img_);
	//transf_nolineal(2, 1, 0.6, img4);
	//Suma(img1, img3);
	//Resta(img3, img1);
	//Multiplicacion(img5);
	//Ejercicio3_2(img5); //no funca
	//Ejercicio5_3(blister_incomp);
	Ejercicio5_2(placa_se);
	waitKey(0);

};