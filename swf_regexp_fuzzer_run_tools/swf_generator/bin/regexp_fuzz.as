package
{
	import flash.display.Sprite;
	
	public class regexp_fuzz extends Sprite
	{
		public function regexp_fuzz()
		{
			var a:RegExp = new RegExp("(?1){5125}(a)");
		}
	}
}