typedef struct elem Element;
typedef struct ob Object;

struct elem{
    GLUquadricObj *pObj;
    double *translate;
    double *rotateX;
    double *rotateY;
    double *color;
    Object *ult;
    Object *ini;
};

struct ob{
    int type;
    double *cord;
    double *translate;
    double *rotate;
    double *color;
    Object *prox;
};


Element * criaElement(double t[], double rx[], double ry[], double c[]){
    Element * e = (Element *) malloc(sizeof(Element));
    e->translate = &t[0];
    e->rotateX = &rx[0];
    e->rotateY = &ry[0];
    e->color = &c[0];
    e->ult = NULL;
    e->ini = NULL;
    return e;
}

//Transladar
double * tl(double x,double y,double z){
    double *a = (double *) malloc(sizeof(double)*3);
    a[0] = x;
    a[1] = y;
    a[2] = z;
    return a;   
}
//Rotacionar
double * rt(double x,double y,double z,double w){
    double *a = (double *) malloc(sizeof(double)*4);
    a[0] = x;
    a[1] = y;
    a[2] = z;
    a[3] = w;
    return a;   
}
//Cor
double * cl(double r,double g,double b){
    double *a = (double *) malloc(sizeof(double)*3);
    a[0] = r;
    a[1] = g;
    a[2] = b;
    return a;   
}
//cord Cilindro
double * cordC(double x,double y,double z,double f, double s){
    double *a = (double *) malloc(sizeof(double)*5);
    a[0] = x;
    a[1] = y;
    a[2] = z;
    a[3] = f;
    a[4] = s;
    return a;   
}
//cord Esfera
double * cordE(double x,double y,double z){
    double *a = (double *) malloc(sizeof(double)*3);
    a[0] = x;
    a[1] = y;
    a[2] = z;
    return a;   
}

//cord Paralelepipedo
double * cordP(double l, double al, double c, double o){
    double *a = (double *) malloc(sizeof(double)*4);
    a[0] = l;
    a[1] = al;
    a[2] = c;
    a[3] = o;
    return a;   
}

//cord Disco
double * cordD(double x,double y,double z, double w){
    double *a = (double *) malloc(sizeof(double)*3);
    a[0] = x;
    a[1] = y;
    a[2] = z;
    a[3] = w;
    return a;   
}


//Adicionar na fila
void addFila(Element *e, Object *o){
    if(e->ini == NULL){
        e->ini = o;
        e->ult = o;
    }else{
        e->ult->prox = o;
        e->ult = o;
    }
}

//Cria Cilindro
void cilindro(Element *e, double cord[], double t[], double r[], double c[]){
    Object * o = (Object *) malloc(sizeof(Object));
    o->type = 0;
    o->cord = &cord[0];
    o->translate = &t[0];
    o->rotate = &r[0];
    o->color = &c[0];
    o->prox = NULL;

    addFila(e, o);
}

//Cria Espera
void esfera(Element *e, double cord[], double t[], double r[], double c[]){
    Object * o = (Object *) malloc(sizeof(Object));
    o->type = 1;
    o->cord = &cord[0];
    o->translate = &t[0];
    o->rotate = &r[0];
    o->color = &c[0];
    o->prox = NULL;

    addFila(e, o);
}

//Cria Cubo
void cubo(Element *e, double cord[], double t[], double r[], double c[]){
    Object * o = (Object *) malloc(sizeof(Object));
    o->type = 2;
    o->cord = &cord[0];
    o->translate = &t[0];
    o->rotate = &r[0];
    o->color = &c[0];
    o->prox = NULL;

    addFila(e, o);
}

//Cria Disco
void disco(Element *e, double cord[], double t[], double r[], double c[]){
    Object * o = (Object *) malloc(sizeof(Object));
    o->type = 3;
    o->cord = &cord[0];
    o->translate = &t[0];
    o->rotate = &r[0];
    o->color = &c[0];
    o->prox = NULL;

    addFila(e, o);
}


void glCubo(double l, double a, double c, double o){
    glBegin(GL_QUADS);

    // FRONT
    glVertex3f(-l, -o, c);
    glVertex3f( o, -o, c);
    glVertex3f( o, a, c);
    glVertex3f(-l, a, c);
    // BACK
    glVertex3f(-l, -o, -o);
    glVertex3f(-l, a, -o);
    glVertex3f( o, a, -o);
    glVertex3f( o, -o, -o);

    // LEFT
    glVertex3f(-l, -o, c);
    glVertex3f(-l, a, c);
    glVertex3f(-l, a, -o);
    glVertex3f(-l, -o, -o);

    // RIGHT
    glVertex3f( o, -o, -o);
    glVertex3f( o, a, -o);
    glVertex3f( o, a, c);
    glVertex3f( o, -o,c);

    // TOP
    glVertex3f(-l, a, c);
    glVertex3f( o, a, c);
    glVertex3f( o, a, -o);
    glVertex3f(-l, a, -o);

    // BOTTOM
    glVertex3f(-l, -o, c);
    glVertex3f(-l, -o, -o);
    glVertex3f( o, -o, -o);
    glVertex3f( o, -o, c);

    glEnd();

}


void compile(Element * e){
    Object * p = e->ini;
    //limpa tudo
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    if(p==NULL){

    }else{
        
        //inicia a pilha da matrix  
        glPushMatrix();
                
        glTranslatef(e->translate[0], e->translate[1], e->translate[2]);  
        glRotatef(e->rotateY[0], e->rotateY[1], e->rotateY[2], e->rotateY[3]);
        glRotatef(e->rotateX[0], e->rotateX[1], e->rotateX[2], e->rotateX[3]);
        if(e->color != NULL){glColor3f(e->color[0], e->color[1], e->color[2]);}  
        
        // Draw something  
        e->pObj = gluNewQuadric();  
        gluQuadricNormals(e->pObj, GLU_SMOOTH); 

        while(p!=NULL){

            if(p->color != NULL) {glColor3f(p->color[0], p->color[1], p->color[2]);}  
        
            glPushMatrix();
            
            if(p->translate != NULL){glTranslatef(p->translate[0], p->translate[1], p->translate[2]);}
            if(p->rotate != NULL){glRotatef(p->rotate[0],p->rotate[1], p->rotate[2], p->rotate[3]);} 
            if(p->type == 0){
                gluCylinder(e->pObj, p->cord[0], p->cord[1], p->cord[2], p->cord[3], p->cord[4]);
            }else if(p->type == 1){
                gluSphere(e->pObj, p->cord[0], p->cord[1], p->cord[2]);
            }else if(p->type == 2){
                glCubo(p->cord[0],p->cord[1], p->cord[2],p->cord[3]);
            }else if(p-> type == 3){
	    	gluDisk(e->pObj, p->cord[0] ,p->cord[1], p->cord[2], p->cord[3]);
	    }

            glPopMatrix();
            p = p->prox;
        }
	
	//OLHO
	////Cabeça 
    	//cubo(e, cordP(1.0f, 1.0f, 0.5f, 1.0f), tl(1.15f,6.5f + tm,0.0f),rt(0,1.0f,0.0f,0.0f), cl(1.0f,1.0f,1.0f));
	glColor3f(1.0f,0.0f,0.0f);	
	glPushMatrix();
	glTranslatef(1.15f, 3.8f, 0.55f);
	gluDisk(e->pObj, 0.1f, 0.4f, 26, 26);
	glPopMatrix();

        glPopMatrix();  
    }      
	//Buffer	
	glutSwapBuffers();
}


