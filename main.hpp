// x, y, z の値を持つ型。
template < typename T >
struct point_3d
{
	point_3d( T x, T y, T z )
		: x_( x )
		, y_( y )
		, z_( z )
	{}
	point_3d( point_3d const & o )
		: x_( o.x_ )
		, y_( o.y_ )
		, z_( o.z_ )
	{}

	T x_, y_, z_;
};

template < typename T >
point_3d< T > operator - ( point_3d< T > const & a )
{
	return point_3d< T >( - a.x_, - a.y_, - a.z_ );
}

typedef point_3d< int >      point_t;
typedef point_3d< unsigned > length_t;

// 点と距離を持つ型。
template < typename T_pos, typename T_length >
class segment
{
public:
	segment( T_pos const & pos, T_length const & size )
		: pos_ ( pos )
		, size_( size )
	{}

	segment( segment const & o )
		: pos_ ( o.pos_ )
		, size_( o.size_ )
	{}

	T_pos end_pos() const
	{
		return pos_ + size_;
	}

	T_pos    pos_;
	T_length size_;
};

// 線分型
typedef segment< int, unsigned >     segment_1d;
// 直方体型
typedef segment< point_t, length_t > segment_3d;

// 線分の重複がある場合に true を返す。
bool is_overlapped( segment_1d const & a, segment_1d const & b )
{
	if( a.pos_ == b.pos_ ) { return true; }
	if( a.pos_ < b.pos_ )  { return a.end_pos() >= b.pos_; }
	                       { return b.end_pos() >= a.pos_; }
}

// 直方体の重複がある場合に true を返す。
bool is_overlapped( segment_3d const & a, segment_3d const & b )
{
	return is_overlapped( segment_1d( a.pos_.x_, a.size_.x_ )
	                    , segment_1d( b.pos_.x_, b.size_.x_ ) )
	    && is_overlapped( segment_1d( a.pos_.y_, a.size_.y_ )
	                    , segment_1d( b.pos_.y_, b.size_.y_ ) )
	    && is_overlapped( segment_1d( a.pos_.z_, a.size_.z_ )
	                    , segment_1d( b.pos_.z_, b.size_.z_ ) );
}

