#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct u16_8 {
	uint8_t al;
	uint8_t ah;
} u16_8;

typedef union t16 {
	u16_8 hl;
	uint16_t ax;
} t16;

typedef struct u32_16 {
	t16 hl16;
	uint16_t none;
} u32_16;

typedef union t32 {
	uint32_t eax;
	u32_16 lhb;
} t32;

typedef enum {
	e32,
	e16,
	h8,
	l8,
	constanta
}flag;

typedef enum {
	o = 111,
	dd = 100,
	u = 117,
	h = 104
} com;

typedef enum {
	a,
	c,
	d,
	e
} reg;

t32 EAX, ECX, EDX;
uint32_t EIP = 1;

int typereg(char* c) {
	if (c[0] == 'A' || c[1] == 'A')
		return 0;
	else if (c[0] == 'C' || c[1] == 'C')
		return 1;
	else if (c[0] == 'D' || c[1] == 'D')
		return 2;
	else
		return 3;
}

int numreg(char* c) {
	if ((int)c[0] + (int)c[1] + (int)c[2] >= 222 && c[2] == 'X')
		return 0;
	else if ((int)c[0] + (int)c[1] >= 153)
		return 1;
	else if ((int)c[0] + (int)c[1] >= 141)
		return 3;
	else
		return 2;
}

t32* destination(reg first) {
	t32* desti = NULL;
	switch (first) {
	case a:
		desti = &EAX;
		break;
	case c:
		desti = &ECX;
		break;
	case d:
		desti = &EDX;
		break;
	case e:
		desti = (t32*)&EIP;
		break;
	}
	return desti;
}

uint32_t flagi(t32* src, flag second) {
	uint32_t srcval;
	switch (second) {
	case e32:
		srcval = src->eax;
		break;
	case e16:
		srcval = src->lhb.hl16.ax;
		break;
	case h8:
		srcval = src->lhb.hl16.hl.ah;
		break;
	case l8:
		srcval = src->lhb.hl16.hl.al;
		break;
	}
	return srcval;
}

void mov(t32* f, flag t, uint32_t c) {
	switch (t) {
	case e32:
		f->eax = c;
		break;
	case e16:
		f->lhb.hl16.ax = (uint16_t)c;
		break;
	case h8:
		f->lhb.hl16.hl.ah = (uint8_t)c;
		break;
	case l8:
		f->lhb.hl16.hl.al = (uint8_t)c;
		break;
	}
}

void add(t32* f, flag t, uint32_t c) {
	switch (t) {
	case e32:
		f->eax += c;
		break;
	case e16:
		f->lhb.hl16.ax += (uint16_t)c;
		break;
	case h8:
		f->lhb.hl16.hl.ah += (uint8_t)c;
		break;
	case l8:
		f->lhb.hl16.hl.al += (uint8_t)c;
		break;
	}
}

void sub(t32* f, flag t, uint32_t c) {
	switch (t) {
	case e32:
		f->eax -= c;
		break;
	case e16:
		f->lhb.hl16.ax -= (uint16_t)c;
		break;
	case h8:
		f->lhb.hl16.hl.ah -= (uint8_t)c;
		break;
	case l8:
		f->lhb.hl16.hl.al -= (uint8_t)c;
		break;
	}
}

void shw(t32* f, flag t) {
	switch (t) {
	case e32:
		printf("0x%x\n", f->eax);
		break;
	case e16:
		printf("0x%x\n", f->lhb.hl16.ax);
		break;
	case h8:
		printf("0x%x\n", f->lhb.hl16.hl.ah);
		break;
	case l8:
		printf("0x%x\n", f->lhb.hl16.hl.al);
		break;
	}
}

int main(void) {
	FILE* f = fopen("test.txt", "r");
	char str[20];
	char* coma;
	uint32_t cons;
	while (fgets(str, sizeof(str), f)) {

		coma = strtok(str, " ");
		if (coma[0] == '\n') {
			continue;
		}
		com co = (com)((int)coma[1]);


		coma = strtok(NULL, " ");
		reg firs_let_reg = (reg)(typereg(coma));
		flag first_flag = (flag)(numreg(coma));


		flag second_flag;
		reg second_let_reg;
		if (co != 104) {
			coma = strtok(NULL, " ");
			if (firs_let_reg == e)
				continue;
			if ((int)coma[0] >= 65) {
				second_flag = (flag)(numreg(coma));
				second_let_reg = (reg)(typereg(coma));
			}
			else
				sscanf(coma, "%i", &cons);
		}

		t32* dest = destination(firs_let_reg);
		switch (co) {
		case o: {
			uint32_t src_val;
			if ((int)coma[0] >= 65) {
				t32* src = destination(second_let_reg);
				src_val = flagi(src, second_flag);
			}
			else
				src_val = cons;
			mov(dest, first_flag, src_val);
			break;
		}
		case dd: {
			uint32_t src_val;
			if ((int)coma[0] >= 65) {
				t32* src = destination(second_let_reg);
				src_val = flagi(src, second_flag);
			}
			else
				src_val = cons;
			add(dest, first_flag, src_val);
			break;
		}
		case u: {
			uint32_t src_val;
			if ((int)coma[0] >= 65) {
				t32* src = destination(second_let_reg);
				src_val = flagi(src, second_flag);
			}
			else
				src_val = cons;
			sub(dest, first_flag, src_val);
			break;
		}
		case h: {
			if (coma[0] == '0' && coma[1] == 'x') {
				uint32_t val;
				sscanf(coma, "%i", &val);
				printf("0x%x\n", val);
			}
			else
				shw(dest, first_flag);
			break;
		}

		}
		EIP++;
	}

	fclose(f);
	return 0;
}