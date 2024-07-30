
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace cv;

// Hypothetical function for pose estimation
// In a real scenario, this function would call a trained model for pose estimation.
int calculate_angle(Point a, Point b, Point c) {
    double ab = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    double bc = sqrt(pow(c.x - b.x, 2) + pow(c.y - b.y, 2));
    double ac = sqrt(pow(c.x - a.x, 2) + pow(c.y - a.y, 2));
    double angle = acos((ab*ab + bc*bc - ac*ac) / (2 * ab * bc));
    return angle * 180 / CV_PI;
}

void track_progress(const char* exercise, int reps) {
    FILE *f = fopen("progress.csv", "a");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(f, "%d-%02d-%02d,%s,%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, exercise, reps);
    fclose(f);
}

int main() {
    VideoCapture cap(0); 
    if (!cap.isOpened()) {
        printf("Error: Could not open camera\n");
        return -1;
    }

    int counter = 0;
    const char* stage = "up";

    while (1) {
        Mat frame;
        cap >> frame; 

        if (frame.empty()) break; 

        // Hypothetical pose estimation points
        Point shoulder(100, 200); // Replace with actual pose estimation
        Point elbow(150, 250);    // Replace with actual pose estimation
        Point wrist(200, 300);    // Replace with actual pose estimation

        int angle = calculate_angle(shoulder, elbow, wrist);

        if (angle > 160) {
            stage = "up";
        }
        if (angle < 30 && strcmp(stage, "up") == 0) {
            stage = "down";
            counter++;
            printf("Push-up count: %d\n", counter);
        }

        // Display the resulting frame
        imshow("AI Personal Trainer", frame);

        if (waitKey(10) == 27) { // Break the loop when ESC key is pressed
            break;
        }
    }

    cap.release();
    destroyAllWindows();

    // Track user progress
    track_progress("Push-ups", counter);

    return 0;
}
