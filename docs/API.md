API Documentation
================
This markup contains the declarations of all of the cfa10036 library's functions.

GPIO
-------------
	int gpio_init();
	int gpio_config(unsigned int pin, unsigned int state);
	int gpio_write(unsigned int portnum, unsigned int state);
	int gpio_read(unsigned int portnum);
	int gpio_close();

Display ( CFA10036 OLED )
-------------
	int display_send();
	int display_fill(unsigned char byte);
	int display_writebuffer(int col, int row, char *string);

I2C
-------------------
	__s32 i2c_smbus_access(int file, char read_write, __u8 command, int size, union i2c_smbus_data *data);
	__s32 i2c_smbus_write_quick(int file, __u8 value);
	__s32 i2c_smbus_read_byte(int file);
	__s32 i2c_smbus_write_byte(int file, __u8 value);
	__s32 i2c_smbus_read_byte_data(int file, __u8 command);
	__s32 i2c_smbus_write_byte_data(int file, __u8 command, __u8 value);
	__s32 i2c_smbus_read_word_data(int file, __u8 command);
	__s32 i2c_smbus_write_word_data(int file, __u8 command, __u16 value);
	__s32 i2c_smbus_process_call(int file, __u8 command, __u16 value);
	__s32 i2c_smbus_read_block_data(int file, __u8 command, __u8 *values);
	__s32 i2c_smbus_write_block_data(int file, __u8 command, __u8 length, const __u8 *values);
	__s32 i2c_smbus_read_i2c_block_data(int file, __u8 command, __u8 length, __u8 *values);
	__s32 i2c_smbus_write_i2c_block_data(int file, __u8 command, __u8 length, const __u8 *values);
	__s32 i2c_smbus_block_process_call(int file, __u8 command, __u8 length, __u8 *values);

Accelerometer ( CFA920 / CFA921 )
-------------------------------------
	bool accel_init();
	double accel_get_x_scale();
	int accel_get_x_raw();
	double accel_get_y_scale();
	int accel_get_y_raw();
	double accel_get_z_scale();
	int accel_get_z_raw();

SPI
--------
	SPIDEV* spi_init(int devno, int bpw, int speed);
	int spi_write_word(SPIDEV* spi_device,void *data);
	int spi_write_chunk(SPIDEV* spi_device,void *data, int count);

Dallas One Wire (Temperature Sensors Only)
------------------------------------------------
	int w1temp_init();
	void w1temp_close();
	int w1temp_getcount();
	double w1temp_get_temp_celsius(int);
	double w1temp_get_temp_fahrenheit(int);
	char *w1temp_getid(int);
