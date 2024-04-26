#pragma once
class Shape {
protected:
	int x, y;
	bool isSelected, isClicked;
	virtual void DrawUnSlctd(System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Gray)) = 0;
	virtual void DrawSlctd(System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::BlueViolet)) = 0;
public:
	virtual void Draw(System::Drawing::Graphics^ g) = 0;
	virtual bool isPointInObj(int x1, int y1) = 0;
	bool getIsSlctd() {
		return isSelected;
	}
	void setIsSlctd(bool slctd) {
		isSelected = slctd;
	}
	void setIsClckd(bool clckd) {
		isClicked = clckd;
	}
	bool getIsClckd() {
		return isClicked;
	}
};

class CCircle :public Shape {
protected: 
	int r;
	void DrawUnSlctd (System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Gray)) override {
		g->FillEllipse(brush, x, y, r * 2, r * 2);
	}
	void DrawSlctd(System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::BlueViolet)) override {
		g->FillEllipse(brush, x, y, r * 2, r * 2);
	}
public:
	CCircle(int _x, int _y) {
		r = 20;
		x = _x - r;
		y = _y - r;
		isClicked = false;
	}
	CCircle(int x, int y, bool slctd) : CCircle(x, y) {
		isSelected = slctd;
	}
	bool isPointInObj(int x1, int y1) override{
		int distanceSquared = (x1 - (x + r)) * (x1 - (x + r)) + (y1 - (y + r)) * (y1 - (y + r));
		return distanceSquared <= r * r;
	}
	void Draw(System::Drawing::Graphics^ g) override {
		if (this->isSelected) DrawSlctd(g);
		else DrawUnSlctd(g);
	}
};
//class CCircle {
//private:
//	int x, y, r;
//	bool isSelected;
//	void DrawUnSlctd(System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Gray)) {
//		g->FillEllipse(brush, x, y, r * 2, r * 2);
//	}
//	void DrawSlctd(System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::BlueViolet)) {
//		g->FillEllipse(brush, x, y, r * 2, r * 2);
//	}
//public:
//	bool isClicked;
//	CCircle(int _x, int _y) {
//		r = 20;
//		x = _x - r;
//		y = _y - r;
//		isClicked = false;
//	}
//	CCircle(int x, int y, bool slctd) : CCircle(x, y) {
//		isSelected = slctd;
//	}
//	void setIsSlctd(bool slctd) {
//		isSelected = slctd;
//	}
//	bool getIsSlctd() {
//		return isSelected;
//	}
//	bool isPointInC(int x1, int y1) {
//		int distanceSquared = (x1 - (x + r)) * (x1 - (x + r)) + (y1 - (y + r)) * (y1 - (y + r));
//		return distanceSquared <= r * r;
//	}
//	void Draw(System::Drawing::Graphics^ g) {
//		if (this->isSelected) DrawSlctd(g);
//		else DrawUnSlctd(g);
//	}
//	void Bleach(System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::White)) {
//		g->FillEllipse(brush, x, y, r * 2, r * 2);
//	}
//
//};