
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int ChangeInt(char num[]); //정수로 변환
char* ChangeRom(int num); //로마자로 변환
int Check_Error(char eq[]); //에러 체크

int main()
{
	int n, ans, check, cnt;
	int reala;
	char op;
	char *eq, *num1, *num2;
	
	num1 = (char*)malloc(sizeof(char) * 30);
	num2 = (char*)malloc(sizeof(char) * 30);


	scanf_s("%d ", &n);
	for (int i = 1; i <= n; i++) {
		eq = (char*)malloc(sizeof(char) * 3000);
		fgets(eq, 3000, stdin);
		int len = strlen(eq);
		if(eq[len-1] == '\n') eq[len-1] = '\0';
		len = strlen(eq);
		check = 0;
		cnt = 0;

		for (int j = 0; j < len; j++) {
			if (eq[j] == '+' || eq[j] == '-' || eq[j] == '*' || eq[j] == '/') {
				num1[cnt] = '\0';

				if (Check_Error(num1) == 1) {
					ans = 0;
				}
				else if (check == 0) {
					op = eq[j];
					ans = ChangeInt(num1);
				}
				else {
					switch (op) {
					case '+': ans = ans + ChangeInt(num1);
						break;
					case '-': ans = ans - ChangeInt(num1);
						break;
					case '*': ans = ans * ChangeInt(num1);
						break;
					case '/':
						if (ChangeInt(num1) == 0) ans = 0;
						else ans = ans / ChangeInt(num1);
					}
					if (ans >= 4000 || ans < 0) ans = 0;
				}

				op = eq[j];
				check = 1;

				free(num1);
				num1 = (char*)malloc(sizeof(char) * 30);
				cnt = 0; //num1초기화
			}

			else if (eq[j] == '=') {
				num1[cnt] = '\0';
				if (Check_Error(num1) == 1) ans = 0;
				else {
					switch (op) {
					case '+': ans = ans + ChangeInt(num1);
						break;
					case '-': ans = ans - ChangeInt(num1);
						break;
					case '*': ans = ans * ChangeInt(num1);
						break;
					case '/': 
						if (ChangeInt(num1) == 0) ans = 0;
						else ans = ans / ChangeInt(num1);
					}
					if (ans >= 4000 || ans < 0) ans = 0;
				}

				int temp = 0;
				for (int k = j+1; k < len; k++) {
					if (eq[k] == ' ') continue;
					else {
						num2[temp] = eq[k];
						temp++;
					}
				}
				num2[temp] = '\0';
				reala = ChangeInt(num2);
				
				if (reala == ans) {
					printf("%d - (%s,%s) PASS\n", i, ChangeRom(ans), num2);
				}
				else {
					printf("%d - (%s,%s) FAIL\n", i, ChangeRom(ans), num2);
				}
				free(num2);
				num2 = (char*)malloc(sizeof(char) * 30);
			}
			else if (eq[j] == ' ') continue;
			else
			{
				num1[cnt] = eq[j];
				//printf("%c ", eq[j]);
				cnt++;
			}
		}
		ans = 0;
		free(eq);
	}

	free(num1);
	free(num2);

	system("pause");
    return 0;
}

int ChangeInt(char num[]) {
	int ans = 0;
	int len = strlen(num);

	for (int i = len-1; i >= 0; i--) {
		switch (num[i]) {
		case 'M': 
			if (num[i - 1] == 'C') ans += 900, i--;
			else ans += 1000;
			break;
		case 'D':
			if (num[i - 1] == 'C') ans += 400, i--;
			else ans += 500;
			break;
		case 'C':
			if (num[i - 1] == 'X') ans += 90, i--;
			else ans += 100;
			break;
		case 'L':
			if (num[i - 1] == 'X') ans += 40, i--;
			else ans += 50;
			break;
		case 'X':
			if (num[i - 1] == 'I') ans += 9, i--;
			else ans += 10;
			break;
		case 'V':
			if (num[i - 1] == 'I') ans += 4, i--;
			else ans += 5;
			break;
		case 'I': ans += 1;
			break;
		case 'Z': ans = 0;
			break;
		default: return 0;
			break;
		}
	}
	if (ans >= 4000) return 0;
	else if (ans < 0) return 0;
	else return ans;
}

char* ChangeRom(int num) {
	char *rnum;
	int cnt = 0;
	rnum = (char*)malloc(sizeof(char) * 30);
	if (num == 0) {
		rnum[0] = 'Z';
		rnum[1] = '\0';
		return rnum;
	}
	else {
		while (num > 0) {
			if (num >= 1000) {
				rnum[cnt] = 'M';
				num = num - 1000;
				cnt++;
			}
			else if (num >= 900) {
				rnum[cnt] = 'C';
				rnum[cnt + 1] = 'M';
				num = num - 900;
				cnt += 2;
			}
			else if (num >= 500) {
				rnum[cnt] = 'D';
				num = num - 500;
				cnt++;
			}
			else if (num >= 400) {
				rnum[cnt] = 'C';
				rnum[cnt + 1] = 'D';
				num = num - 400;
				cnt += 2;
			}
			else if (num >= 100) {
				rnum[cnt] = 'C';
				num = num - 100;
				cnt++;
			}
			else if (num >= 90) {
				rnum[cnt] = 'X';
				rnum[cnt + 1] = 'C';
				num = num - 90;
				cnt += 2;
			}
			else if (num >= 50) {
				rnum[cnt] = 'L';
				num = num - 50;
				cnt++;
			}
			else if (num >= 40) {
				rnum[cnt] = 'X';
				rnum[cnt + 1] = 'L';
				num = num - 40;
				cnt += 2;
			}
			else if (num >= 10) {
				rnum[cnt] = 'X';
				num = num - 10;
				cnt++;
			}
			else if (num >= 9) {
				rnum[cnt] = 'I';
				rnum[cnt + 1] = 'X';
				num = num - 9;
				cnt += 2;
			}
			else if (num >= 5) {
				rnum[cnt] = 'V';
				num = num - 5;
				cnt++;
			}
			else if (num >= 4) {
				rnum[cnt] = 'I';
				rnum[cnt + 1] = 'V';
				num = num - 4;
				cnt += 2;
			}
			else {
				rnum[cnt] = 'I';
				num = num - 1;
				cnt++;
			}
		}
	}
	rnum[cnt] = '\0';

	return rnum;
}

int Check_Error(char eq[]) {
	
	if (strcmp(eq, ChangeRom(ChangeInt(eq)))) {
		return 1;
	}
	else return 0;
}
