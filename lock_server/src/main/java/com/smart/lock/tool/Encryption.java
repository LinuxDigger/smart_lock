package com.smart.lock.tool;

import java.nio.ByteBuffer;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.KeyFactory;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.KeySpec;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Base64;
import java.util.Base64.Decoder;
import java.util.Base64.Encoder;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.spec.SecretKeySpec;

import org.apache.commons.codec.DecoderException;
import org.apache.commons.codec.binary.Hex;

import com.smart.lock.Config;

public class Encryption {
	private static MessageDigest sha256;
	private static SecretKeyFactory PBKDF2;
	private static Cipher AES;
	private static Encoder base64Encoder;
	private static Decoder base64Decoder;
	private static KeyPairGenerator RSAKeyGen4096;
	private static KeyFactory RSAKeyFactory;
	private static Cipher RSA;

	private static SecureRandom random;

	// 初始化加密算法，java这些算法都是自带的。
	// 加密或者解密前，一定要先调用这个函数初始化。
	public static boolean init() throws NoSuchPaddingException {
		try {
			sha256 = MessageDigest.getInstance("SHA-256");
			PBKDF2 = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA256");
			AES = Cipher.getInstance("AES/CBC/PKCS5Padding");
			base64Encoder = Base64.getEncoder();
			base64Decoder = Base64.getDecoder();
			RSAKeyGen4096 = KeyPairGenerator.getInstance("RSA");
			RSAKeyGen4096.initialize(4096);
			RSAKeyFactory = KeyFactory.getInstance("RSA");
			RSA = Cipher.getInstance("RSA");

			random = new SecureRandom();
		} catch (NoSuchAlgorithmException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return false;
		}
		return true;
	}

	// 二进制编码为base64字符串
	public static String encodeBase64(byte[] data) {
		return base64Encoder.encodeToString(data);
	}

	// 解码base64编码的二进制
	public static byte[] decodeBase64(String data) {
		return base64Decoder.decode(data);
	}

	// 计算sha256
	public static byte[] sha256(byte[] data) {
		return sha256.digest(data);
	}

	// 把long一共64位，8个byte，little-endian 的存储格式
	public static byte[] longToBytes(long x) {
		ByteBuffer buffer = ByteBuffer.allocate(Long.BYTES);
		buffer.putLong(x);
		return buffer.array();
	}

	public static byte[] tSHA(long timestamp) {
		return sha256.digest(longToBytes(timestamp));
	}

	// 每一次将数组的长度减半，如果原来长度为奇数，结果的长度为原来的长度加一减半。
	public static byte[] halfBytes(byte[] bytes) {
		int len = (bytes.length + 1) / 2;
		byte[] half = Arrays.copyOfRange(bytes, 0, len);
		for (int i = len; i < bytes.length; ++i)
			half[i - len] ^= bytes[i];
		return half;
	}

	// 拼接多个byte数组。
	public static byte[] concatArrays(byte[]... arrays) {
		int len = 0, loc = 0;
		for (byte[] bs : arrays)
			len += bs.length;
		byte[] res = new byte[len];
		for (byte[] bs : arrays) {
			System.arraycopy(bs, 0, res, loc, bs.length);
			loc += bs.length;
		}
		return res;
	}

	// 通过 timestamp ID IMEI credential 计算AES密码。
	public static byte[] genAESKey(long timestamp, String ID, String IMEI, byte[] credential)
			throws DecoderException, InvalidKeySpecException {
//		if (0 >= timestamp)
//			throw new IllegalArgumentException("The timestamp must larger than 0.");
		byte[] tSHA = tSHA(timestamp);
		ArrayList<Byte> cre = new ArrayList<Byte>(256 / 2 * 4 + 16 + 16);
		// 循环取凭证。
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < tSHA.length; ++j)
				for (int k = 7; k >= 0; --k) {
					if (0 == (tSHA[j] >> k & 1))
						continue;
					int index = (j * 8 + 7 - k) * 4 + i;
					cre.add(credential[index]);
				}
		byte[] _tSHA = halfBytes(halfBytes(halfBytes(halfBytes(tSHA))));
		// 循环取IMEI。
		for (int j = 0; j < _tSHA.length; ++j)
			for (int k = 7; k >= 0; --k) {
				if (0 == (_tSHA[j] >> k & 1))
					continue;
				int index = j * 8 + 7 - k;
				if (index < 15)
					cre.add((byte) IMEI.charAt(index));
			}
		cre.add((byte) (_tSHA[1] & 1));
		byte[] IDBytes = Hex.decodeHex(ID.toCharArray());
		for (byte b : IDBytes)
			cre.add(b);
		// 如果需要效率的话，使用sha256计算hash。
//		byte[] _cre = new byte[cre.size()];
//		for (int i = 0; i < _cre.length; ++i)
//			_cre[i] = cre.get(i);
//		return sha256.digest(_cre);
		// 如果追求更加安全的话，使用PBKDF2
		char[] _cre = new char[cre.size()];
		for (int i = 0; i < _cre.length; ++i)
			_cre[i] = (char) (byte) cre.get(i);
		// 这里是用char来计算的，如果c语言用byte来计算，可能计算结果不一致，到时候我们再讨论怎么修改。
		// 其中Config.PBKDF2Round = 131;
		KeySpec PBEKey = new PBEKeySpec(_cre, tSHA, Config.PBKDF2Round, 256);
		SecretKey hash = PBKDF2.generateSecret(PBEKey);
		return hash.getEncoded();
	}

	// 使用AES加密，我们使用AES/CBC/PKCS5Padding模式，其中的IV使用halfBytes(tSHA)
	public static byte[] AESEncryption(long timestamp, byte[] key, byte[] data) throws InvalidKeyException,
			InvalidAlgorithmParameterException, IllegalBlockSizeException, BadPaddingException {
		byte[] tSHA = tSHA(timestamp);
		AES.init(Cipher.ENCRYPT_MODE, new SecretKeySpec(key, "AES"), new IvParameterSpec(halfBytes(tSHA)));
		return AES.doFinal(data);
	}

	// 使用AES解密。
	public static byte[] AESDecryption(long timestamp, byte[] key, byte[] data) throws InvalidKeyException,
			InvalidAlgorithmParameterException, IllegalBlockSizeException, BadPaddingException {
		byte[] tSHA = tSHA(timestamp);
		AES.init(Cipher.DECRYPT_MODE, new SecretKeySpec(key, "AES"), new IvParameterSpec(halfBytes(tSHA)));
		return AES.doFinal(data);
	}

	public static KeyPair newRSAKeyPair() {
		KeyPair keyPair = RSAKeyGen4096.generateKeyPair();
//		keyPair.getPrivate().getEncoded();
//		keyPair.getPublic().getEncoded();
		return keyPair;
	}

	public static PublicKey getPublicKey(String base64PublicKey) throws InvalidKeySpecException {
		X509EncodedKeySpec keySpec = new X509EncodedKeySpec(decodeBase64(base64PublicKey));
		return RSAKeyFactory.generatePublic(keySpec);
	}

	public static PrivateKey getPrivateKey(String base64PrivateKey) throws InvalidKeySpecException {
		PKCS8EncodedKeySpec keySpec = new PKCS8EncodedKeySpec(decodeBase64(base64PrivateKey));
		return RSAKeyFactory.generatePrivate(keySpec);
	}

	public static byte[] RSAEncryption(String base64PublicKey, byte[] data)
			throws InvalidKeyException, InvalidKeySpecException, IllegalBlockSizeException, BadPaddingException {
		RSA.init(Cipher.ENCRYPT_MODE, getPublicKey(base64PublicKey));
		return RSA.doFinal(data);
	}

	public static byte[] RSADecryption(String base64PrivateKey, byte[] data)
			throws InvalidKeyException, InvalidKeySpecException, IllegalBlockSizeException, BadPaddingException {
		RSA.init(Cipher.DECRYPT_MODE, getPrivateKey(base64PrivateKey));
		return RSA.doFinal(data);
	}

	public static byte[] RSAAESEncryption(String base64PublicKey, byte[] data)
			throws InvalidKeyException, InvalidKeySpecException, IllegalBlockSizeException, BadPaddingException,
			InvalidAlgorithmParameterException {
		byte[] AESKey = new byte[32];
		byte[] iv = new byte[16];
		random.nextBytes(AESKey);
		random.nextBytes(iv);
		AES.init(Cipher.ENCRYPT_MODE, new SecretKeySpec(AESKey, "AES"), new IvParameterSpec(iv));
		byte[] encrypted = AES.doFinal(data);
		return concatArrays(RSAEncryption(base64PublicKey, AESKey), iv, encrypted);
	}

	public static byte[] RSAAESDecryption(String base64PrivateKey, byte[] data)
			throws InvalidKeyException, InvalidKeySpecException, IllegalBlockSizeException, BadPaddingException,
			InvalidAlgorithmParameterException {
		byte[] AESKeyEncrypted = new byte[512];
		byte[] AESKey;
		byte[] iv = new byte[16];
		int dataLocation = 0;
		System.arraycopy(data, dataLocation, AESKeyEncrypted, 0, AESKeyEncrypted.length);
		dataLocation += AESKeyEncrypted.length;
		System.arraycopy(data, dataLocation, iv, 0, iv.length);
		dataLocation += iv.length;
		AESKey = RSADecryption(base64PrivateKey, AESKeyEncrypted);

		byte[] _data = new byte[data.length - dataLocation];
		System.arraycopy(data, dataLocation, _data, 0, _data.length);
		dataLocation += _data.length;
		AES.init(Cipher.DECRYPT_MODE, new SecretKeySpec(AESKey, "AES"), new IvParameterSpec(iv));
		return AES.doFinal(_data);
	}

}
