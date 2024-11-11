#pragma once

namespace KUtil
{
	template <typename T>
	struct TTypeTraits
	{
		using MemEfficientCopyT = std::conditional_t<sizeof(T) <= sizeof(void*), T, const T&>;
	};

	//~Property
	template <typename T>
	class TPropertyData
	{
	protected:
		using PropertyType = T;
		using CopyType = typename TTypeTraits<T>::MemEfficientCopyT;
		
	public:
		template <typename... P>
		explicit constexpr TPropertyData(P&&... ParamArgs) : Property(std::forward<P>(ParamArgs)...) { }

		[[nodiscard]]
		constexpr CopyType GetProperty() const { return Property; }

	protected:
		T Property;
	};

	template <typename T>
	class TProperty : public TPropertyData<T>
	{
		using Super = TPropertyData<T>;
		
	public:
		using Super::TPropertyData;

		void SetProperty(typename Super::CopyType Value)
		{
			Super::Property = Value;
		}
	};
	//~Property End
}
