#include<stdio.h>
#include<string.h>
/*
         - - -
         - - -
         - - -
         a b c  
 - - - 1 - - - 1 - - -
 - - - 2 - - - 2 - - -
 - - - 3 - - - 3 - - -
         a b c
         - - -
         - - -
         - - -
*/
int m[6][3][3];
char wincfg;
 
char pl(int pla){
    switch(pla){
    case 1:
        return 'X';
        break;
    case 0:
        return '-';
        break;
    case -1:
        return 'O';
        break;
    default:
        return '?';
    }
}
 
int drawMap(){
    int i,j,k;//map,col,row
 
    for (j=0;j<3;j++) printf("         %c %c %c\n",pl(m[1][0][j]),pl(m[1][1][j]),pl(m[1][2][j]));
    printf("         \x1b[32ma b c\x1b[0m\n");
    for (j=0;j<3;j++) printf(" %c %c %c \x1b[32m%d\x1b[0m %c %c %c \x1b[32m%d\x1b[0m %c %c %c\n",\
        pl(m[4][0][j]),pl(m[4][1][j]),pl(m[4][2][j]),j+1,\
        pl(m[0][0][j]),pl(m[0][1][j]),pl(m[0][2][j]),j+1,\
        pl(m[2][0][j]),pl(m[2][1][j]),pl(m[2][2][j]));
    printf("         \x1b[32ma b c\x1b[0m\n");
    for (j=0;j<3;j++) printf("         %c %c %c\n",pl(m[3][0][j]),pl(m[3][1][j]),pl(m[3][2][j]));
    printf("         \x1b[32ma b c\x1b[0m\n");
    for (j=0;j<3;j++) printf("         %c %c %c\n",pl(m[5][0][j]),pl(m[5][1][j]),pl(m[5][2][j]));/**/
 
    return 0;
}

int drawMapWithWinner(char winsymbol){
    int i, x,y, dx, dy;
    drawMap();
    
    x=10; y=5;
    if (wincfg == 'd') {dx=2; dy=1;}
    else if (wincfg == 'x') {y+=2; dx=2; dy=-1;}
    else if (wincfg >= '1' && wincfg <= '3') {y+=wincfg-'1'; dx=2; dy=0;}
    else if (wincfg >= 'a' && wincfg <= 'c') {x+=2*(wincfg-'a'); dx=0; dy=1;}
    else return 0;
    
    printf("\x1b[1;31m");
    for (i=0; i<=2; ++i){
        printf("\033[%d;%dH%c",y,x,winsymbol);
        x+=dx;
        y+=dy;
    }
    printf("\x1b[0m");
    printf("\033[15;15H");
    return 0;
}

int isSideFull(int s){
    int c,r;
    for (c=0; c<3; ++c){
        for(r=0;r<3;++r){
            if (m[s][c][r] == 0) return 0;
        }
    }
    return 1;
}
 
int getWinner(){
    int s;
    if(m[0][0][0] != 0 && m[0][0][0] == m[0][1][0] && m[0][0][0] == m[0][2][0]) {wincfg='1'; return m[0][0][0];}
    if(m[0][0][1] != 0 && m[0][0][1] == m[0][1][1] && m[0][0][1] == m[0][2][1]) {wincfg='2'; return m[0][0][1];}
    if(m[0][0][2] != 0 && m[0][0][2] == m[0][1][2] && m[0][0][2] == m[0][2][2]) {wincfg='3'; return m[0][0][2];}
    if(m[0][0][0] != 0 && m[0][0][0] == m[0][0][1] && m[0][0][0] == m[0][0][2]) {wincfg='a'; return m[0][0][0];}
    if(m[0][1][0] != 0 && m[0][1][0] == m[0][1][1] && m[0][1][0] == m[0][1][2]) {wincfg='b'; return m[0][1][0];}
    if(m[0][2][0] != 0 && m[0][2][0] == m[0][2][1] && m[0][2][0] == m[0][2][2]) {wincfg='c'; return m[0][2][0];}
    if(m[0][0][0] != 0 && m[0][0][0] == m[0][1][1] && m[0][0][0] == m[0][2][2]) {wincfg='d'; return m[0][0][0];}
    if(m[0][2][0] != 0 && m[0][2][0] == m[0][1][1] && m[0][2][0] == m[0][0][2]) {wincfg='x'; return m[0][2][0];}
    
    for (s=0;s<6;++s){
        if (!isSideFull(s)) return 0;
    }

    return 100;
}
 
void getString(char* ch,int length){
    int i;
    for(i=0;(*(ch+i) = getchar()) != EOF && *(ch+i) != '\n';i++) if(i >= length - 1) i = length - 1;
    *(ch+i) = 0;
}

void rotClockwise(int map){
    int i;
    i = m[map][0][0];
    m[map][0][0] = m[map][0][2];
    m[map][0][2] = m[map][2][2];
    m[map][2][2] = m[map][2][0];
    m[map][2][0] = i;
 
    i = m[map][0][1];
    m[map][0][1] = m[map][1][2];
    m[map][1][2] = m[map][2][1];
    m[map][2][1] = m[map][1][0];
    m[map][1][0] = i;
 
}
void rotCounterClockwise(int map){
    int i;
    i = m[map][0][0];
    m[map][0][0] = m[map][2][0];
    m[map][2][0] = m[map][2][2];
    m[map][2][2] = m[map][0][2];
    m[map][0][2] = i;
 
    i = m[map][0][1];
    m[map][0][1] = m[map][1][0];
    m[map][1][0] = m[map][2][1];
    m[map][2][1] = m[map][1][2];
    m[map][1][2] = i;
}
 
void clrbuff(){
    int ch;
    while((ch=getchar()) != EOF && ch != '\n');
}

void copystr(char* to, char* from, int length){
	int i;
	for(i=0;i<length;i++){
		*(to+i) = *(from + i);
	}
}
 
int moveCommand(char* scom){
    //r(a-c)(u,d)
    int i;
    char com[4];
    
    copystr(&com[0],scom,4);
    
    if (com[1] >= 'a' && com[1] <= 'c'){
        com[1]-=97;
        switch(com[2]){
            case 'u':
                if (com[1] == 2) rotClockwise(2);
                else if (com[1] == 0) rotCounterClockwise(4);
                i = m[0][com[1]][0];
                m[0][com[1]][0] = m[3][com[1]][0];
                m[3][com[1]][0] = m[5][com[1]][0];
                m[5][com[1]][0] = m[1][com[1]][0];
                m[1][com[1]][0] = i;
 
                i = m[0][com[1]][1];
                m[0][com[1]][1] = m[3][com[1]][1];
                m[3][com[1]][1] = m[5][com[1]][1];
                m[5][com[1]][1] = m[1][com[1]][1];
                m[1][com[1]][1] = i;
                 
                i = m[0][com[1]][2];
                m[0][com[1]][2] = m[3][com[1]][2];
                m[3][com[1]][2] = m[5][com[1]][2];
                m[5][com[1]][2] = m[1][com[1]][2];
                m[1][com[1]][2] = i;
                break;
            case 'd':
                if (com[1] == 0) rotClockwise(2);
                else if (com[1] == 2) rotCounterClockwise(4);
                i = m[0][com[1]][0];
                m[0][com[1]][0] = m[1][com[1]][0];
                m[1][com[1]][0] = m[5][com[1]][0];
                m[5][com[1]][0] = m[3][com[1]][0];
                m[3][com[1]][0] = i;
 
                i = m[0][com[1]][1];
                m[0][com[1]][1] = m[1][com[1]][1];
                m[1][com[1]][1] = m[5][com[1]][1];
                m[5][com[1]][1] = m[3][com[1]][1];
                m[3][com[1]][1] = i;
 
                i = m[0][com[1]][2];
                m[0][com[1]][2] = m[1][com[1]][2];
                m[1][com[1]][2] = m[5][com[1]][2];
                m[5][com[1]][2] = m[3][com[1]][2];
                m[3][com[1]][2] = i;
                break;
            default:
                printf("Third char is wrong!\n");
                return 1;
                break;
        }
    }else
 
    //r(1-3)(l,r)
    if (com[1] >= '1' && com[1] <= '3'){
        com[1]-=49;
        switch(com[2]){
            case 'l':
                if (com[1] == 0) rotClockwise(1);
                else if (com[1] == 2) rotCounterClockwise(3);
                i = m[0][0][com[1]];
                m[0][0][com[1]] = m[2][0][com[1]];
                m[2][0][com[1]] = m[5][2][com[1]];
                m[5][2][com[1]] = m[4][0][com[1]];
                m[4][0][com[1]] = i;
 
                i = m[0][1][com[1]];
                m[0][1][com[1]] = m[2][1][com[1]];
                m[2][1][com[1]] = m[5][1][com[1]];
                m[5][1][com[1]] = m[4][1][com[1]];
                m[4][1][com[1]] = i;
 
                i = m[0][2][com[1]];
                m[0][2][com[1]] = m[2][2][com[1]];
                m[2][2][com[1]] = m[5][0][com[1]];
                m[5][0][com[1]] = m[4][2][com[1]];
                m[4][2][com[1]] = i;
                break;
            case 'r':
                if (com[1] == 2) rotClockwise(3);
                else if (com[1] == 0) rotCounterClockwise(1);
                i = m[0][0][com[1]];
                m[0][0][com[1]] = m[4][0][com[1]];
                m[4][0][com[1]] = m[5][2][2-com[1]];
                m[5][2][2-com[1]] = m[2][0][com[1]];
                m[2][0][com[1]] = i;
 
                i = m[0][1][com[1]];
                m[0][1][com[1]] = m[4][1][com[1]];
                m[4][1][com[1]] = m[5][1][2-com[1]];
                m[5][1][2-com[1]] = m[2][1][com[1]];
                m[2][1][com[1]] = i;
 
                i = m[0][2][com[1]];
                m[0][2][com[1]] = m[4][2][com[1]];
                m[4][2][com[1]] = m[5][0][2-com[1]];
                m[5][0][2-com[1]] = m[2][2][com[1]];
                m[2][2][com[1]] = i;
                break;
            default:
                printf("Third char is wrong!\n");
                return 1;
                break;
        }
    }else
 
    //ru(c,k)
    if (com[1] == 'u'){
        switch(com[2]){
            case 'c':
                rotClockwise(0);
                i = m[1][0][2];
                m[1][0][2] = m[4][2][2];
                m[4][2][2] = m[3][2][0];
                m[3][2][0] = m[2][0][0];
                m[2][0][0] = i;
 
                i = m[1][1][2];
                m[1][1][2] = m[4][2][1];
                m[4][2][1] = m[3][1][0];
                m[3][1][0] = m[2][0][1];
                m[2][1][0] = i;
 
                i = m[1][2][2];
                m[1][2][2] = m[4][2][0];
                m[4][2][0] = m[3][0][0];
                m[3][0][0] = m[2][0][2];
                m[2][0][2] = i;
                break;
            case 'k':
                rotCounterClockwise(0);
                i = m[1][0][2];
                m[1][0][2] = m[2][0][0];
                m[2][0][0] = m[3][2][0];
                m[3][2][0] = m[4][2][2];
                m[4][2][2] = i;
 
                i = m[1][1][2];
                m[1][1][2] = m[2][0][1];
                m[2][1][0] = m[3][1][0];
                m[3][1][0] = m[4][2][1];
                m[4][2][1] = i;
 
                i = m[1][2][2];
                m[1][2][2] = m[2][0][2];
                m[2][0][2] = m[3][0][0];
                m[3][0][0] = m[4][2][0];
                m[4][2][0] = i;
                break;
            default:
                printf("Third char is wrong!\n");
                return 1;
                break;
        }
    }else{
 
    //wrong
        printf("Second char is wrong!\n");
        return 1;
    }
    return 0;
}

char negate(char ch){
	switch(ch){
		case 'u':
			return 'd';
		break;
		case 'd':
			return 'u';
		break;
		case 'l':
			return 'r';
		break;
		case 'r':
			return 'l';
		break;
		case 'c':
			return 'k';
		break;
		case 'k':
			return 'c';
		break;
	}
	return '#';
}

void printActions(){
    printf("In-game commands are case sensitive, always use lowercase!\n");
    
    printf("\nActions:\n");
    printf("- place player symbol: <char coordinate><num coordinate>\n");
    printf("    e.g.: a1, c3\n");
    printf("- rotate column: r<char coordinate><direction>\n");
    printf("  direction can be 'u' for up or 'd' for down\n");
    printf("    e.g.: rad, rcu\n");
    printf("- rotate row: r<num coordinate><direction>\n");
    printf("  direction can be 'l' for left or 'r' for right\n");
    printf("    e.g.: r2r, r3l\n");
    printf("- rotate slice: r<slice coordinate><direction>\n");
    printf("  currently slice coordinate can only be 'u' for upper\n");
    printf("  direction can be 'c' for clockwise or 'k' for counterclockwise\n");
    printf("    e.g.: ruc, ruk\n");
}

void printUsage(){
    printf("Usage:\n");
    printf("rubikamob [options]\n");
    
    printf("\nOptions:\n");
    printf("  --help: print this message\n");
    
    printf("\n");
    printActions();
}
 
int main(int argc, char** argv){
 
    char com[6];
    char precom[6];
    
    int player=1;
    int step =0;
    int* intp;
    int i,col,row; 
    int win = 0;
    wincfg = 0;
    
    if (argc > 1){
        if (!strncmp("--help", argv[1], 7)){
            printUsage();
        } else {
            printf("Failed to process argument: %s\n", argv[1]);
            printUsage();
        }
        return 0;
    }

    
    for(intp = &m[0][0][0];(intp-&m[0][0][0])<54;intp++){
        *intp=0;
    }

    printf("\033[2J\033[0;0H");
    while(win == 0){
        drawMap();
        printf("\n\nTurn: %c - ",pl(player));
        
        getString(&com[0],4);
        printf("\033[2J\033[0;0H");

        if (!com[0]){             
            printf("Type '?' for help.\n");
            continue;
        } else if (com[0]=='?'){
            printActions();
            printf("\nPress enter to continue...");
            getString(&com[0],2);
            printf("\033[2J\033[0;0H");
            continue;
        } else if (com[0]=='r'){
        	precom[2] = negate(precom[2]);
        	if (strncmp(com,precom,4) == 0){
        		com[2] = precom[2] = negate(precom[2]);
        		printf("Opposite operation can not be performed! (Previous: %s)\n",com);
        		continue;
        	}else{
                precom[2] = negate(precom[2]);
            }
            if (moveCommand(&com[0]) == 1) {
                printf("Type '?' for help.\n");
                continue;
            }
        }else{
            col = com[0] - 'a';
            row = com[1] - '1';
             
            if(col< 3 && col >-1 && row< 3 && row >-1){
                if (m[0][col][row]==0){
                    m[0][col][row]=player;
                    step++;
                }else{
                    printf("Area not empty!\n");
                    continue;
                }
            }else{
                printf("Out of bounds!\n");
                printf("Type '?' for help.\n");
                continue;
            }
        }
        
        copystr(&precom[0],&com[0],4);
        win = getWinner();
        player *=-1;
    }
 
    drawMapWithWinner(pl(win));
    if(wincfg) printf("\n\nWinner: %c\n", pl(win));
    else printf("\n\nRound draw!\n");
 
    return 0;
}
