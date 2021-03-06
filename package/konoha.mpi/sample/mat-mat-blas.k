using konoha.mpi.*;
using lib.blas.*;
using konoha.math.*;

N = (|$script.argv| > 0) ? (int)$script.argv[0] : 256;
DEBUG = 1;
EPS =   1.0e-18

/* Please define the matrices in here */
a = new double[N,N];
b = new double[N,N];
c = new double[N,N];

int     myid, numprocs;

void myMatMat(double[] c, double[] a, double[] b, int n);

void main(String[] args) {

    double  t0, t1, t2;
    double  dc_inv, d_mflops;

    int     ierr;
    int     i, j;
    int     iflag;

    world = MPIComm.WORLD;
    myid = world.getRank();
    numprocs = world.getSize();

    /* matrix generation --------------------------*/
    if (DEBUG == 1) {
        for(j=0; j<N; j++) {
            for(i=0; i<N; i++) {
                a[j,i] = 1.0;
                b[j,i] = 1.0;
                c[j,i] = 0.0;
            }
        }
    } else {
        for(j=0; j<N; j++) {
            for(i=0; i<N; i++) {
                a[j,i] = Float.random();
                b[j,i] = Float.random();
                c[j,i] = 0.0;
            }
        }
    } /* end of matrix generation --------------------------*/

    /* Start of mat-vec routine ----------------------------*/
    world.barrier();
    t1 = getMPIWtime();

    MyMatMat(c, a, b, N);

    world.barrier();
    t2 = getMPIWtime();
    t0 =  t2 - t1;
    t_w = new float[1];
    world.reduce((MPIData)[t0], (MPIData)t_w, 1, MPIOp.MAX, 0);
    /* End of mat-vec routine --------------------------- */

    if (myid == 0) {

        OUT.println("N  = "+N);
        OUT.println("Mat-Mat time  = "+"%f"(t_w[0])+" [sec.]");

        d_mflops = 2.0 * (double)N * (double)N * (double)N / t_w[0];
        d_mflops = d_mflops * 1.0e-6;
        OUT.println(" "+"%f"(d_mflops)+" [MFLOPS]");
    }

    if (DEBUG == 1) {
        /* Verification routine ----------------- */
        iflag = 0;
        for(j=0; j<N; j++) {
            for(i=0; i<N; i++) {
                if (Math.fabs(c[j,i] - (double)N) > EPS) {
                    OUT.println(" Error! in ( "+"%d"(j)+" , "+"%d"(i)+" ) th argument.");
                    iflag = 1;
                    break;
                }
            }
        }
        /* ------------------------------------- */

        if (myid == 0) {
            if (iflag == 0) OUT.println(" OK! ");
        }

    }

}

void myMatMat(double[] c, double[] a, double[] b, int n)
{
    /*
      Blas.dgemm: Matrix-Matrix-Mul
        C = beta * C + alpha * (A * B)
            a, b, c: Matrix (2-dim array vector)
            alpha, beta: Scalar
     */
    Blas.dgemm(Blas.ORDER_COLMAJOR, Blas.TRANSPOSE_NOTRANS, Blas.TRANSPOSE_NOTRANS,
               n /* a.rows */, n /* b.rows */, n /* c.rows */,
               1.0 /* alpha */, a, n /* a.cols */, b, n /* b.cols */, 0.0 /* beta */, c, n /* c.cols*/);
}
