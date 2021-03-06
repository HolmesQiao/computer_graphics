#include "draw.h"

Line::Line(GLint x_began, GLint y_began, GLint x_end, GLint y_end, GLint color[3]){
    began.change_color(color);
    end.change_color(color);
    began.change_pos(x_began, y_began);
    began.change_color(color);
    end.change_pos(x_end, y_end);
    end.change_color(color);
    k = (GLfloat)(end.y - began.y) / (GLfloat)(end.x - began.x);
    for (int i = 0; i < 3; i++) this->color[i] = (GLubyte)color[i];
}
void Line::renew_k(){k = (GLfloat)(end.y - began.y) / (GLfloat)(end.x - began.x);}

void draw_line(void){
    for (int i = 0; i < line_vector.size(); i++){
	GLint began_x, began_y, end_x, end_y;
	if (line_vector[i].k >= 0){
	    if (line_vector[i].began.x <= line_vector[i].end.x){
		began_x = line_vector[i].began.x, began_y = line_vector[i].began.y;
		end_x = line_vector[i].end.x, end_y = line_vector[i].end.y;
	    }else{
		began_x = line_vector[i].end.x, began_y = line_vector[i].end.y;
		end_x = line_vector[i].began.x, end_y = line_vector[i].began.y;
	    }
	}else{
	    if (line_vector[i].began.x <= line_vector[i].end.x){
		began_x = line_vector[i].end.x, began_y = line_vector[i].end.y;
		end_x = line_vector[i].began.x, end_y = line_vector[i].began.y;
	    }else{
		began_x = line_vector[i].began.x, began_y = line_vector[i].began.y;
		end_x = line_vector[i].end.x, end_y = line_vector[i].end.y;
	    }
	}
	GLfloat delta_y = end_y - began_y;
	GLfloat delta_x = end_x - began_x;
	GLint y_k = began_y, x_k = began_x;
	GLfloat k = (GLfloat)(end_y - began_y) / (GLfloat)(end_x - began_x);
	int p = 2 * delta_y - delta_x;
	int delta = line_vector[i].k >= 0 ? 1 : -1;

	glRasterPos2f(began_x / window_width, began_y / window_height);
	glDrawPixels(POINT_WIDTH, POINT_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, line_vector[i].began.color);
	glRasterPos2f(end_x / window_width, end_y / window_height);
	glDrawPixels(POINT_WIDTH, POINT_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, line_vector[i].end.color);

	if (k <= 1 && k >= 0){
	    for (GLint j = began_x; j != end_x; j += delta){
		if (p < 0) p = p + 2 * delta_y;
		else{
		    y_k++;
		    p = p + 2 * delta_y - 2 * delta_x;
		}
		glRasterPos2f((float)j / window_width, (float)y_k / window_height);
		glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, line_vector[i].color);
	    }
	}else if (k > 1){
	    for (GLint j = began_y; j != end_y; j++){
		if (p < 0) p = p + 2 * delta_x;
		else{
		    x_k += delta;
		    p = p + 2 * delta_x - 2 * delta_y;
		}
		glRasterPos2f((float)x_k / window_width, (float)j / window_height);
		glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, line_vector[i].color);
	    }
	}
    }
}
