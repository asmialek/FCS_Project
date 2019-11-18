/*########################################*/
/*### Port from matlab fix() function ####*/
/*########################################*/

int fix(double in){
    int out;

    if (in >= 0.0){
       out = (int)floor(in);
    }
    else if (in < 0.0){
       out = (int)ceil(in);
    }

    return out;
}

/* port from matlab sign() function */
int sign(double in){
    int out;

    if (in > 0.0){
       out = 1;
    }
    else if (in < 0.0){
       out = -1;
    }
    else if (in == 0.0){
       out = 0;
    }
    return out;
}