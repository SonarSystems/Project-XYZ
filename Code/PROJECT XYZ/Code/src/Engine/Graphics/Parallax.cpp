#include "Graphics/Parallax.hpp"

namespace Sonar
{  
	Parallax::Parallax( GameDataRef data ) : _data( data )
	{
		_speed = 100;

		_direction = Parallax::DIRECTION::LEFT;

		_isSingleScroll = false;
	}

	Parallax::~Parallax( ) { }

	void Parallax::SetBackgrounds( const std::vector<Sprite *> &backgrounds )
	{
		_backgrounds = backgrounds;

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

						_backgrounds.at( i )->SetPositionX( _backgrounds.at( lastID )->GetPositionX( ) + _backgrounds.at( lastID )->GetWidth( ) + ( -_speed * dt ) );
					}
					else
					{
						const int lastID = i - 1;

						_backgrounds.at( i )->SetPositionX( _backgrounds.at( lastID )->GetPositionX( ) + _backgrounds.at( lastID )->GetWidth( ) );
					}
				}
			}
			else if ( Parallax::DIRECTION::RIGHT == _direction )
			{
				_backgrounds.at( i )->MoveX( dt * _speed );

				if ( _backgrounds.at( i )->GetPositionX( ) > _data->window.getSize( ).x )
				{
					if ( 0 == i )
					{
						const int lastID = _backgrounds.size( ) - 1;

						_backgrounds.at( i )->SetPositionX( _backgrounds.at( lastID )->GetPositionX( ) - _backgrounds.at( i )->GetWidth( ) + ( _speed * dt ) );
					}
					else
					{
						const int lastID = i - 1;

						_backgrounds.at( i )->SetPositionX( _backgrounds.at( lastID )->GetPositionX( ) - _backgrounds.at( i )->GetWidth( ) );
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

						_backgrounds.at( i )->SetPositionY( _backgrounds.at( lastID )->GetPositionY( ) + _backgrounds.at( lastID )->GetHeight( ) + ( -_speed * dt ) );
					}
					else
					{
						const int lastID = i - 1;

						_backgrounds.at( i )->SetPositionY( _backgrounds.at( lastID )->GetPositionY( ) + _backgrounds.at( lastID )->GetHeight( ) );
					}
				}
			}
			else if ( Parallax::DIRECTION::DOWN == _direction )
			{
				_backgrounds.at( i )->MoveY( dt * _speed );

				if ( _backgrounds.at( i )->GetPositionY( ) > _data->window.getSize( ).y )
				{
					if ( 0 == i )
					{
						const int lastID = _backgrounds.size( ) - 1;

						_backgrounds.at( i )->SetPositionY( _backgrounds.at( lastID )->GetPositionY( ) - _backgrounds.at( i )->GetHeight( ) + ( _speed * dt ) );
					}
					else
					{
						const int lastID = i - 1;

						_backgrounds.at( i )->SetPositionY( _backgrounds.at( lastID )->GetPositionY( ) - _backgrounds.at( i )->GetHeight( ) );
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
		_direction = direction;

		SetBackgroundPositions( );
	}

	Sonar::Parallax::Parallax::DIRECTION Parallax::GetDirection( ) const
	{ return _direction; }

	void Parallax::Move( const Parallax::DIRECTION &direction, const float &speed )
	{
		_direction = direction;
		_speed = speed;
		_isSingleScroll = true;
	}

	void Parallax::SetBackgroundPositions( )
	{
		for ( int i = 0; i < _backgrounds.size( ); i++ )
		{
			if ( Parallax::DIRECTION::LEFT == _direction )
			{
				if ( 0 == i )
				{ _backgrounds.at( i )->SetPosition( 0, 0 ); }
				else
				{
					_backgrounds.at( i )->SetPosition
					(
						_backgrounds.at( i - 1 )->GetPositionX( ) + _backgrounds.at( i - 1 )->GetWidth( ),
						0
					);
				}
			}
			else if ( Parallax::DIRECTION::RIGHT == _direction )
			{
				if ( 0 == i )
				{ _backgrounds.at( i )->SetPosition( 0, 0 ); }
				else
				{
					_backgrounds.at( i )->SetPosition
					(
						_backgrounds.at( i - 1 )->GetPositionX( ) - _backgrounds.at( i )->GetWidth( ),
						0
					);
				}
			}
			else if ( Parallax::DIRECTION::UP == _direction )
			{
				if ( 0 == i )
				{ _backgrounds.at( i )->SetPosition( 0, 0 ); }
				else
				{
					_backgrounds.at( i )->SetPosition
					(
						0,
						_backgrounds.at( i - 1 )->GetPositionY( ) + _backgrounds.at( i - 1 )->GetHeight( )
					);
				}
			}
			else if ( Parallax::DIRECTION::DOWN == _direction )
			{
				if ( 0 == i )
				{ _backgrounds.at( i )->SetPosition( 0, 0 ); }
				else
				{
					_backgrounds.at( i )->SetPosition
					(
						0,
						_backgrounds.at( i - 1 )->GetPositionY( ) - _backgrounds.at( i )->GetHeight( )
					);
				}
			}
		}
	}
}
