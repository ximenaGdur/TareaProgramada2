#ifndef GENETIC_ALGORITHM_DRAW_CPP
#define GENETIC_ALGORITHM_DRAW_CPP
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <stdio.h>
#include <stdlib.h>
#define RENDER_EPOCH_EVERY 50

#include "GeneticAlgorithm.h"
/* -------- ADD YOUR INCLUDE HERE -------- */
#include "TravellingSalesman.h"
/* -------- ADD YOUR INCLUDE HERE -------- */


// Object identifiers
enum{
	ID_MAINPANEL = 1,
	ID_EPOINPUT = 11,
	ID_POPINPUT = 12,
	ID_HOFINPUT = 13,
	ID_MUTINPUT = 14,
	ID_NEWINPUT = 15,
	ID_EPOTEXT = 21,
	ID_POPTEXT = 22,
	ID_HOFTEXT = 23,
	ID_MUTTEXT = 24,
	ID_NEWTEXT = 25,
	ID_RESETBUTTON = 31,
	ID_GOTOBUTTON = 32,
	ID_NEXTBUTTON = 33,
	ID_UPDATECANVAS = 101,
};

// Class declarations
class DrawApp : public wxApp{
	public:
    	virtual bool OnInit();
};

class Canvas2D : public wxGLCanvas {
	public:
    	Canvas2D(wxFrame* parent, wxSize size);
    	~Canvas2D();
    	void Redraw();
    private:
		wxGLContext *context;
};

class MainWindow : public wxFrame{
	public:
    	MainWindow();
    	~MainWindow();
	private:
    	void OnExit(wxCommandEvent& event);
	    void OnAbout(wxCommandEvent& event);
	    void OnSize(wxSizeEvent& event);
	    void OnMaximize(wxMaximizeEvent& event);
	    void ResetGA(wxCommandEvent& event);
	    void GotoGA(wxCommandEvent& event);
	    void NextGA(wxCommandEvent& event);
	    void UpdateEvent(wxThreadEvent& event);
	    void UpdateState();
	    float Clamp(float value, float min, float max);
	    char statusBarReport[256];
		wxMenu* menu;
		wxMenuBar* menuBar;
		wxPanel *mainPanel;
		wxTextCtrl *epoInput,*popInput,*hofInput,*mutInput,*newInput;
		wxStaticText *epoText,*popText,*hofText,*mutText,*newText;
		wxButton *resetButton,*gotoButton,*nextButton;
		Canvas2D* canvas;
		GeneticAlgorithm* ga;
		float** points;
		float bestResult;
		unsigned int numPoints,epoch,lastUpdate;
		friend class Canvas2D;
};

class ProcessingThread : public wxThread{
	public:
		ProcessingThread(MainWindow *frame,GeneticAlgorithm* ga,float** points,float* bestResult,unsigned int *numPoints,unsigned int *epoch,unsigned int targetEpoch);
		virtual void* Entry();
	private:
		MainWindow *frame;
		GeneticAlgorithm* ga;
		float **points,*bestResult;
		unsigned int *numPoints,*epoch, targetEpoch;
};

// "main function" macro
wxIMPLEMENT_APP(DrawApp);

// Function declarations
bool DrawApp::OnInit(){
	MainWindow* main = new MainWindow();
	SetTopWindow(main);
	main->Show(true);
	return true;
}

MainWindow::MainWindow() : wxFrame(0, wxID_ANY, "Genetic Algorithm Visualizer"){
	/* ------------- MODIFY TO YOUR CONSTRUCTOR --------------------*/
	ga = new TravellingSalesman(100,0.1f,0.3f,0.05f);
	/* ------------- MODIFY TO YOUR CONSTRUCTOR --------------------*/
	points = new float*[2048];
	for(unsigned int i=0;i<2048;i++){ points[i] = new float[2]; }
	lastUpdate = -1;
	epoch = ga->getEpoch();
	bestResult = ga->getBestIndividual();
	ga->drawBestIndividual(points,numPoints);
	// UI Creation
	menu = new wxMenu();
	menu->Append(wxID_ABOUT);
	menu->AppendSeparator();
	menu->Append(wxID_EXIT);
	menuBar = new wxMenuBar;
	menuBar->Append(menu, "&Menu");
	SetMenuBar(menuBar);
	CreateStatusBar();
//	Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
//	Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_SIZE, &MainWindow::OnSize, this);
	Bind(wxEVT_THREAD, &MainWindow::UpdateEvent, this, wxID_ANY);
	mainPanel = new wxPanel(this, ID_MAINPANEL, wxPoint(25, 25), wxSize(530, 400));
	canvas = new Canvas2D((wxFrame*) mainPanel,wxSize(530,400));
	epoInput = new wxTextCtrl(this, ID_EPOINPUT, "1", wxPoint(125, 435), wxSize(40,20));
	popInput = new wxTextCtrl(this, ID_POPINPUT, "100", wxPoint(125, 475), wxSize(40,20));
	hofInput = new wxTextCtrl(this, ID_HOFINPUT, "0.01", wxPoint(275, 435), wxSize(40,20));
	mutInput = new wxTextCtrl(this, ID_MUTINPUT, "0.3", wxPoint(275, 475), wxSize(40,20));
	newInput = new wxTextCtrl(this, ID_NEWINPUT, "0.05", wxPoint(425, 435), wxSize(40,20));
	epoText = new wxStaticText(this, ID_EPOTEXT, "Epoch:", wxPoint(70,437), wxSize(40,20));
	popText = new wxStaticText(this, ID_POPTEXT, "Population:", wxPoint(50,477), wxSize(60,20));
	hofText = new wxStaticText(this, ID_HOFTEXT, "Hall of fame:", wxPoint(190,437), wxSize(70,20));
	mutText = new wxStaticText(this, ID_MUTTEXT, "Mutations:", wxPoint(200,477), wxSize(60,20));
	newText = new wxStaticText(this, ID_NEWTEXT, "Newcomers:", wxPoint(340,437), wxSize(70,20));
	resetButton = new wxButton(this, ID_RESETBUTTON, "Reset", wxPoint(340, 475), wxSize(60,20));
	gotoButton = new wxButton(this, ID_GOTOBUTTON, "Go to", wxPoint(420, 475), wxSize(60,20));
	nextButton = new wxButton(this, ID_NEXTBUTTON, "Next", wxPoint(500, 475), wxSize(60,20));
	epoInput->SetEditable(false);
//	resetButton->Bind(wxEVT_BUTTON, MainWindow::ResetGA, this);
//	gotoButton->Bind(wxEVT_BUTTON, MainWindow::GotoGA, this);
//	nextButton->Bind(wxEVT_BUTTON, MainWindow::NextGA, this);
	SetMinSize(wxSize(600,600));
	SetSize(0,0,600,600);
	Center();
}
MainWindow::~MainWindow(){
	delete ga;
	for(unsigned int i=0;i<2048;i++){ delete[] points[i]; }
	delete[] points;
}

void MainWindow::OnExit(wxCommandEvent& event){	Close(true); }
void MainWindow::OnAbout(wxCommandEvent& event){
    wxMessageBox("Genetic Algorithm Visualizer by Pablo Sauma","About GAV", wxOK | wxICON_INFORMATION);
}
void MainWindow::OnSize(wxSizeEvent& event){
	int width,height;
	GetSize(&width,&height);
	mainPanel->SetSize(wxSize(width-70,height-200));
	canvas->SetSize(wxSize(width-70,height-200));
	epoInput->SetPosition(wxPoint(epoInput->GetPosition().x,height-165));
	popInput->SetPosition(wxPoint(popInput->GetPosition().x,height-125));
	hofInput->SetPosition(wxPoint(hofInput->GetPosition().x,height-165));
	mutInput->SetPosition(wxPoint(mutInput->GetPosition().x,height-125));
	newInput->SetPosition(wxPoint(newInput->GetPosition().x,height-165));
	epoText->SetPosition(wxPoint(epoText->GetPosition().x,height-163));
	popText->SetPosition(wxPoint(popText->GetPosition().x,height-123));
	hofText->SetPosition(wxPoint(hofText->GetPosition().x,height-163));
	mutText->SetPosition(wxPoint(mutText->GetPosition().x,height-123));
	newText->SetPosition(wxPoint(newText->GetPosition().x,height-163));
	resetButton->SetPosition(wxPoint(resetButton->GetPosition().x,height-125));
	gotoButton->SetPosition(wxPoint(gotoButton->GetPosition().x,height-125));
	nextButton->SetPosition(wxPoint(nextButton->GetPosition().x,height-125));
	canvas->Redraw();
}
void MainWindow::OnMaximize(wxMaximizeEvent& event){
	wxSizeEvent e;
	OnSize(e);
}

void MainWindow::ResetGA(wxCommandEvent& event){
	unsigned int pop = atoi(popInput->GetValue());
	float hof = Clamp(atof(hofInput->GetValue()),0.0,0.9);
	float mut = Clamp(atof(mutInput->GetValue()),0.0,0.99999); 
	float spo = Clamp(atof(newInput->GetValue()),0.0,0.9-hof);
	ga->reset(pop,hof,mut,spo);
	epoch = ga->getEpoch();
	bestResult = ga->getBestIndividual();
	ga->drawBestIndividual(points,numPoints);
	UpdateState();
}
void MainWindow::GotoGA(wxCommandEvent& event){
	wxTextEntryDialog* gotoInput = new wxTextEntryDialog(this, "Introduce the epoch you want to go to:", "Generation jump");
	gotoInput->ShowModal();
	int targetEpoch = atoi(gotoInput->GetValue());
	ProcessingThread *thread = new ProcessingThread(this,ga,points,&bestResult,&numPoints,&epoch,targetEpoch);
	if(thread->Run() != wxTHREAD_NO_ERROR){
		delete thread;
	}
}
void MainWindow::NextGA(wxCommandEvent& event){
	ga->epoch();
	epoch = ga->getEpoch();
	bestResult = ga->getBestIndividual();
	ga->drawBestIndividual(points,numPoints);
	UpdateState();
}
void MainWindow::UpdateEvent(wxThreadEvent& event){
	UpdateState();
}
void MainWindow::UpdateState(){
	char str[16];
	if(lastUpdate!=epoch){
		lastUpdate = epoch;
		printf("Epoch: %i, best solution: %.2f\n",epoch,bestResult);
		sprintf(str,"%i",epoch);
		epoInput->SetValue(str);
		sprintf(statusBarReport,"Current best solution: %.2f",bestResult);
		SetStatusText(statusBarReport);
		canvas->Redraw();
	}
}
float MainWindow::Clamp(float value, float min, float max){
	if(value>max){ value=max; }
	if(value<min){ value=min; }
	return value;
}

ProcessingThread::ProcessingThread(MainWindow *frame,GeneticAlgorithm* ga,float** points,float* bestResult,unsigned int *numPoints,unsigned int *epoch,unsigned int targetEpoch) : wxThread(wxTHREAD_DETACHED){
	this->frame = frame;
	this->ga = ga;
	this->points = points;
	this->bestResult = bestResult;
	this->numPoints = numPoints;
	this->epoch = epoch;
	this->targetEpoch = targetEpoch;
}
void* ProcessingThread::Entry(){
	unsigned int tmpEpoch = *epoch;
	unsigned int tmpBestResult = *bestResult;
	if(targetEpoch>tmpEpoch){
		wxCommandEvent event(wxEVT_THREAD, ID_UPDATECANVAS);
		unsigned int lastUpdate = tmpEpoch;
		do{
			ga->epoch();
			tmpEpoch++;
			float newResult = ga->getBestIndividual();
			if(tmpEpoch%1000==0 || tmpBestResult!=newResult){
				*epoch = ga->getEpoch();
				ga->drawBestIndividual(points,*numPoints);
				*bestResult = newResult;
				if((tmpEpoch-lastUpdate)>RENDER_EPOCH_EVERY){
					wxPostEvent(frame, event);
					lastUpdate = tmpEpoch;
				}
				tmpBestResult = newResult;
			}
		} while(tmpEpoch<targetEpoch);
		if(tmpEpoch != lastUpdate){
			*epoch = ga->getEpoch();
			ga->drawBestIndividual(points,*numPoints);
			wxPostEvent(frame, event);
		}
	}
	return 0;
}

Canvas2D::Canvas2D(wxFrame* parent, wxSize size):wxGLCanvas(parent, wxID_ANY, 0,  wxDefaultPosition, size, 0, wxT("2d")){
	context = new wxGLContext(this);
	SetCurrent(*context);
}
Canvas2D::~Canvas2D(){}

void Canvas2D::Redraw(){
	if(IsShown()) {
        wxClientDC dc(this);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
        float** points = ((MainWindow*)(GetParent()->GetParent()))->points;
        unsigned int numPoints = ((MainWindow*)(GetParent()->GetParent()))->numPoints;
		float minx,maxx,miny,maxy,delta,cx,cy;
		if(numPoints){
			minx = points[0][0];
			maxx = points[0][0];
			miny = points[0][1];
			maxy = points[0][1];
		}
		for(unsigned int i=1;i<numPoints;i++){
			if(points[i][0]<minx){ minx = points[i][0]; }
			if(points[i][0]>maxx){ maxx = points[i][0]; }
			if(points[i][1]<miny){ miny = points[i][1]; }
			if(points[i][1]>maxy){ maxy = points[i][1]; }
		}
		cx = (maxx+minx)/2.0f;
		cy = (maxy+miny)/2.0f;
		delta = (((maxx-minx)>(maxy-miny))?(maxx-minx):(maxy-miny))*1.125f;
		minx = cx - delta/2.0f;
		maxx = cx + delta/2.0f;
		miny = cy - delta/2.0f;
		maxy = cy + delta/2.0f;
		// Axis
		glBegin(GL_LINES);
        	glColor3f(0.0, 1.0, 1.0);
        	if(minx<=0 && maxx>=0){
				float x = ((0.0f-minx)/(maxx-minx))*2.0f - 1.0f;
				glVertex2f(x,-1);
				glVertex2f(x,1);
			}
            if(miny<=0 && maxy>=0){
				float y = ((0.0f-miny)/(maxy-miny))*2.0f - 1.0f;
				glVertex2f(-1,y);
				glVertex2f(1,y);	
			}
        glEnd();
		// Path
		glBegin(GL_LINE_STRIP);
            glColor3f(1.0, 0.0, 0.0);
            for(unsigned int i=0;i<=numPoints;i++){
				float x = ((points[i%numPoints][0]-minx)/(maxx-minx))*2.0f - 1.0f;
				float y = ((points[i%numPoints][1]-miny)/(maxy-miny))*2.0f - 1.0f;
				glVertex2f(x,y);
			}
        glEnd();
		// Points
		glPointSize(10.0f);
        glBegin(GL_POINTS);
        	glColor3f(1.0, 0.5, 0.0);
        	for(unsigned int i=0;i<numPoints;i++){
				float x = ((points[i][0]-minx)/(maxx-minx))*2.0f - 1.0f;
				float y = ((points[i][1]-miny)/(maxy-miny))*2.0f - 1.0f;
				glVertex2f(x,y);
			}
    	glEnd();  
		glFlush();
        SwapBuffers();
    }
}
#endif
