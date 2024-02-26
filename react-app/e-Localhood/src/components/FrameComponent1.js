import "./FrameComponent1.css";

const FrameComponent1 = ({ pincode }) => {
  return (
    <div className="area-street-shop-no">
      <div className="pincode">{pincode}</div>
      <div className="vector-icon1">
        <input className="arrows" type="text" />
        <div className="this-has-to">This has to be in Maharashtra</div>
      </div>
    </div>
  );
};

export default FrameComponent1;
