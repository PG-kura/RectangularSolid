#include "main.hpp"
#include <assert.h>

typedef segment_3d C;

template < bool is_nega >
C make_C( int x, int y, int z, unsigned w, unsigned h, unsigned d )
{
	point_t p( x, y, z );
	return C( is_nega? - p: p, length_t( w, h, d ) );
}

// c0 と c1 が同一の場合は重複
template < bool is_nega >
void test1()
{
	C c0 = make_C< is_nega >( 1, 2, 3, 4, 5, 6 );
	C c1 = c0;

	assert( is_overlapped( c0, c1 ) );
}

// c0 が c1 に空間を開けて内包される場合は重複
template < bool is_nega >
void test2()
{
	C c0 = make_C< is_nega >( 2, 2, 2,  6,  6,  6 );
	C c1 = make_C< is_nega >( 0, 0, 0, 10, 10, 10 );

	assert( is_overlapped( c0, c1 ) );
}

// c0 が c1 の始点側に内接する場合は重複
template < bool is_nega >
void test3()
{
	C c0 = make_C< is_nega >( 4, 5, 6, 1, 2, 3 );
	C c1 = make_C< is_nega >( 4, 4, 6, 2, 4, 4 );

	assert( is_overlapped( c0, c1 ) );
}

// c0 が c1 の終点側に内接する場合は重複
template < bool is_nega >
void test4()
{
	C c0 = make_C< is_nega >( 5, 5, 5, 1, 2, 3 );
	C c1 = make_C< is_nega >( 4, 4, 4, 2, 3, 4 );

	assert( is_overlapped( c0, c1 ) );
}

// c0 と c1 が x, y, z それぞれで交わっている場合は重複
template < bool is_nega >
void test5()
{
	C c0 = make_C< is_nega >( 1, 2, 3, 4, 5, 6 );
	C c1 = make_C< is_nega >( 3, 4, 5, 6, 7, 8 );

	assert( is_overlapped( c0, c1 ) );
}

// c0 と c1 が x だけで交わっている場合は重複とみなさない。
template < bool is_nega >
void test6()
{
	C c0 = make_C< is_nega >( 1, 2, 3, 4, 5, 6 );
	C c1 = make_C< is_nega >( 2, 8, 10, 4, 5, 5 );

	assert( ! is_overlapped( c0, c1 ) );
}

// c0 と c1 が y だけで交わっている場合は重複とみなさない。
template < bool is_nega >
void test7()
{
	C c0 = make_C< is_nega >( 1, 2, 3, 4, 5, 6 );
	C c1 = make_C< is_nega >( 6, 3, 10, 5, 5, 5 );

	assert( ! is_overlapped( c0, c1 ) );
}

// c0 と c1 が z だけで交わっている場合は重複とみなさない。
template < bool is_nega >
void test8()
{
	C c0 = make_C< is_nega >( 1, 2, 3, 4, 5, 6 );
	C c1 = make_C< is_nega >( 6, 8, 4, 5, 5, 6 );

	assert( ! is_overlapped( c0, c1 ) );
}

template < bool is_nega >
void tests()
{
	test1< is_nega >();
	test2< is_nega >();
	test3< is_nega >();
	test4< is_nega >();
	test5< is_nega >();
	test6< is_nega >();
	test7< is_nega >();
	test8< is_nega >();
}

int main()
{
	// x, y, z をそれぞれそのまま使ってテスト
	tests< false >();

	// x, y, z をそれぞれ反転させてテスト
	tests< true >();
}

