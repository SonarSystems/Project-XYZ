#include "Graphics/Parallax.hpp"

namespace Sonar
{  
	Parallax::Parallax( GameDataRef data ) : _data( data )
	{
		_speed = 100;

		_originalDirection = _direction = Parallax::DIRECTION::LEFT;
		_orientation = Parallax::ORIENTATION::HORIZONTAL;

		_isSingleScroll = false;

		_offsetX = _offsetY = 0;
	}

	Parallax::~Parallax( ) { }

	void Parallax::SetBackgrounds( const std::vector<Sprite *> &backgrounds )
	{
		_backgrounds = backgrounds;

		SetBackgroundPositions( );
	}

	void Parallax::SetBackgrounds( const std::vector<std::string> &backgrounds )
	{
		for ( auto filepath : backgrounds )
		{ _backgrounds.push_back( new Sprite( _data, filepath ) ); }

		SetBackgroundPositions( );
	}

	void Parallax::Update( const float &dt )
	{
		for ( int i = 0; i < _backgrounds.size( ); i++ )
		{
			if ( Parallax::DIRECTION::LEFT == _direction )
			{
				_backgrounds.at( i )->MoveX( dt * -_speed );

				if ( _backgrounds.at( i )->GetPositionX( ) + _backgrounds.at( i )->GetWidth( ) < 0 )
				{
					if ( 0 == i )
					{
						const int lastID = _backgrounds.size( ) - 1;

						_backgrounds.at( i )->SetPositionX( _backgrounds.at( lastID )->GetPositionX( ) + _backgrounds.at( lastID )->GetWidth( ) + _offsetX + ( -_speed * dt ) );
					}
					else
					{
						const int lastID = i - 1;

						_backgrounds.at( i )->SetPositionX( _backgrounds.at( lastID )->GetPositionX( ) + _backgrounds.at( lastID )->GetWidth( ) + _offsetX );
					}
				}
			}
			else if ( Parallax::DIRECTION::RIGHT == _direction )
			{
				_backgrounds.at( i )->MoveX( dt * _speed );

				if ( _backgrounds.at( i )->GetPositionX( ) > _data->window.getSize( ).x )
				{
					if ( _backgrounds.size( ) - 1 == i )
					{
						const int lastID = 0;

						_backgrounds.at( i )->SetPositionX( _backgrounds.at( lastID )->GetPositionX( ) - _backgrounds.at( i )->GetWidth( ) - _offsetX );
					}
					else
					{
						const int lastID = i + 1;

						_backgrounds.at( i )->SetPositionX( _backgrounds.at( lastID )->GetPositionX( ) - _backgrounds.at( i )->GetWidth( ) - _offsetX + ( _speed * dt ) );
					}
				}
			}
			else if ( Parallax::DIRECTION::UP == _direction )
			{
				_backgrounds.at( i )->MoveY( dt * -_speed );

				if ( _backgrounds.at( i )->GetPositionY( ) + _backgrounds.at( i )->GetHeight( ) < 0 )
				{
					if ( 0 == i )
					{
						const int lastID = _backgrounds.size( ) - 1;

						_backgrounds.at( i )->SetPositionY( _backgrounds.at( lastID )->GetPositionY( ) + _backgrounds.at( lastID )->GetHeight( ) + _offsetY + ( -_speed * dt ) );
					}
					else
					{
						const int lastID = i - 1;

						_backgrounds.at( i )->SetPositionY( _backgrounds.at( lastID )->GetPositionY( ) + _backgrounds.at( lastID )->GetHeight( ) + _offsetY );
					}
				}
			}
			else if ( Parallax::DIRECTION::DOWN == _direction )
			{
				_backgrounds.at( i )->MoveY( dt * _speed );

				if ( _backgrounds.at( i )->GetPositionY( ) > _data->window.getSize( ).y )
				{
					if ( _backgrounds.size( ) - 1 == i )
					{
						const int lastID = 0;

						_backgrounds.at( i )->SetPositionY( _backgrounds.at( lastID )->GetPositionY( ) - _backgrounds.at( i )->GetHeight( ) - _offsetY );
					}
					else
					{
						const int lastID = i + 1;

						_backgrounds.at( i )->SetPositionY( _backgrounds.at( lastID )->GetPositionY( ) - _backgrounds.at( i )->GetHeight( ) - _offsetY + ( _speed * dt ) );
					}
				}
			}
		}

		if ( _isSingleScroll )
		{
			_speed = 0;
			_isSingleScroll = false;
		}
	}

	void Parallax::Draw( )
	{
		for ( auto &background : _backgrounds )
		{ background->Draw( ); }
	}

	void Parallax::SetSpeed( const float &speed )
	{
		_speed = speed;

		if ( speed < 0 )
		{ _speed = 0; }
		else
		{ _speed = speed; }
	}

	float Parallax::GetSpeed( ) const
	{ return _speed; }

	void Parallax::SetDirection( const Parallax::DIRECTION &direction )
	{
		_originalDirection = _direction = direction;

		if ( Parallax::DIRECTION::LEFT == direction || Parallax::DIRECTION::RIGHT == direction )
		{ _orientation = Parallax::ORIENTATION::HORIZONTAL; }
		else
		{ _orientation = Parallax::ORIENTATION::VERTICAL; }

		SetBackgroundPositions( );
	}

	Sonar::Parallax::Parallax::DIRECTION Parallax::GetDirection( ) const
	{ return _direction; }

	void Parallax::SetOrientation( const Parallax::ORIENTATION &orientation )
	{ _orientation = orientation; }

	Sonar::Parallax::Parallax::ORIENTATION Parallax::GetOrientation( ) const
	{ return _orientation; };

	void Parallax::SetScrollToManual( const Parallax::ORIENTATION &orientation )
	{
		_orientation = orientation;
		_speed = 0;

		if ( Parallax::ORIENTATION::HORIZONTAL == orientation )
		{ SetDirection( Parallax::DIRECTION::RIGHT ); }
		else
		{ SetDirection( Parallax::DIRECTION::DOWN ); }
	}

	void Parallax::Move( const Parallax::DIRECTION &direction, const float &speed )
	{
		_direction = direction;
		_speed = speed;
		_isSingleScroll = true;
	}

	void Parallax::Reset( )
	{
		_direction = _originalDirection;
		SetBackgroundPositions( );
	}

	void Parallax::SetOffset( const float &offsetX, const float &offsetY )
	{
		_offsetX = offsetX;
		_offsetY = offsetY;

		SetBackgroundPositions( );
	}

	void Parallax::SetBackgroundPositions( )
	{
		if ( Parallax::DIRECTION::LEFT == _direction )
		{
			for ( int i = 0; i < _backgrounds.size( ); i++ )
			{
				if ( 0 == i )
				{ _backgrounds.at( i )->SetPosition( _offsetX, _offsetY ); }
				else
				{
					_backgrounds.at( i )->SetPosition
					(
						_backgrounds.at( i - 1 )->GetPositionX( ) + _backgrounds.at( i - 1 )->GetWidth( ) + _offsetX,
						_offsetY
					);
				}
			}
		}
		else if ( Parallax::DIRECTION::RIGHT == _direction )
		{
			for ( int i = _backgrounds.size( ) - 1; i >= 0; i-- )
			{
				if ( _backgrounds.size( ) - 1 == i )
				{ _backgrounds.at( i )->SetPosition( _offsetX, _offsetY ); }
				else
				{
					_backgrounds.at( i )->SetPosition
					(
						_backgrounds.at( i + 1 )->GetPositionX( ) - _backgrounds.at( i )->GetWidth( ) - _offsetX,
						_offsetY
					);
				}
			}
		}
		else if ( Parallax::DIRECTION::UP == _direction )
		{
			for ( int i = 0; i < _backgrounds.size( ); i++ )
			{
				if ( 0 == i )
				{ _backgrounds.at( i )->SetPosition( _offsetX, _offsetY ); }
				else
				{
					_backgrounds.at( i )->SetPosition
					(
						_offsetX,
						_backgrounds.at( i - 1 )->GetPositionY( ) + _backgrounds.at( i - 1 )->GetHeight( ) + _offsetY
					);
				}
			}
		}
		else if ( Parallax::DIRECTION::DOWN == _direction )
		{
			for ( int i = _backgrounds.size( ) - 1; i >= 0; i-- )
			{
				if ( _backgrounds.size( ) - 1 == i )
				{ _backgrounds.at( i )->SetPosition( _offsetX, _offsetY ); }
				else
				{
					_backgrounds.at( i )->SetPosition
					(
						_offsetX,
						_backgrounds.at( i + 1 )->GetPositionY( ) - _backgrounds.at( i )->GetHeight( ) - _offsetY
					);
				}
			}
		}
	}
}