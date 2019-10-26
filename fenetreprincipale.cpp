#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include "fleche.h"
#include <QGraphicsRectItem>

FenetrePrincipale::FenetrePrincipale(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    scene->setBackgroundBrush(Qt::white);

    QRectF rect(-5, -5, 10, 10);

    QGraphicsPolygonItem *rectangle1 = new QGraphicsPolygonItem(rect);
    rectangle1->setX(-350);
    rectangle1->setY(150);
    scene->addItem(rectangle1);
    rectangle1->setFlag(QGraphicsItem::ItemIsSelectable);
    rectangle1->setFlag(QGraphicsItem::ItemIsMovable);
    rectangle1->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    QGraphicsPolygonItem *rectangle2 = new QGraphicsPolygonItem(rect);
    scene->addItem(rectangle2);

    rectangle2->setFlag(QGraphicsItem::ItemIsSelectable);
    rectangle2->setFlag(QGraphicsItem::ItemIsMovable);
    rectangle2->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    Fleche *fleche = new Fleche(rectangle1, rectangle2);
    scene->addItem(fleche);
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

