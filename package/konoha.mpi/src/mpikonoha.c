/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2006-2011, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2011-      Yutaro Hiraoka <utr.hira at gmail.com>
 *           (c) 2008-      Konoha Team konohaken@googlegroups.com
 * All rights reserved.
 *
 * You may choose one of the following two licenses when you use konoha.
 * If you want to use the latter license, please contact us.
 *
 * (1) GNU General Public License 3.0 (with K_UNDER_GPL)
 * (2) Konoha Non-Disclosure License 1.0
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include<konoha1.h>
#include<errno.h>
#include<mpi.h>

#ifdef __cplusplus
extern "C" {
#endif

int main(int argc, const char *argv[])
{
	MPI_Init(&argc, (char***)&argv);
	konoha_ginit(argc, argv);
	konoha_t konoha = konoha_open();
	int _world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &_world_rank);
#ifdef KNH_MPI_PROFILE
	double _begin = MPI_Wtime();
#endif
	konoha_main(konoha, argc, argv);
#ifdef KNH_MPI_PROFILE
	double _finish = MPI_Wtime();
	double _duration = _finish - _begin;
	{
		CTX ctx = (CTX)konoha;
		KNH_NTRACE2(ctx, "konoha_main(MPI)", K_NOTICE,
					KNH_LDATA(LOG_f("begin", _begin), LOG_f("finish", _finish), LOG_f("duration", _duration), LOG_i("myrank", _world_rank)));
	}
#endif
	konoha_close(konoha);
	MPI_Finalize();
	return 0;
}

#ifdef __cplusplus
}
#endif
